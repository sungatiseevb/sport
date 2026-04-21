# Домашнее задание

## Схема базы данных

```
customers   (id, name, email, country, registered_at)
orders      (id, customer_id, order_date, status, total_amount)
order_items (order_id, product_id, quantity, price_at_purchase)
products    (id, name, category, price, stock)
```

Связи: `customers 1-N orders`, `orders 1-N order_items`, `products 1-N order_items`

---

## Часть I - Теория: оконные функции vs GROUP BY

### а) Принципиальная разница

`GROUP BY` схлопывает строки - из N строк с одинаковым ключом получается одна, исходные данные теряются. Оконная функция сохраняет все строки и просто добавляет к каждой вычисленное значение.

```sql
-- GROUP BY: было 4 строки → стало 2
SELECT category, AVG(price) FROM products GROUP BY category;

-- Оконная функция: все 4 строки на месте, AVG добавлен рядом
SELECT name, price, AVG(price) OVER (PARTITION BY category) FROM products;
```

### б) Синтаксис OVER

`OVER()` - обязательная часть, именно она делает функцию оконной. Остальное опционально. `PARTITION BY` делит строки на независимые группы (как GROUP BY, но без схлопывания). `ORDER BY` задаёт порядок внутри группы - обязателен для `ROW_NUMBER`, `LAG`, `LEAD` и скользящих агрегатов. `ROWS BETWEEN` уточняет рамку: какие строки вокруг текущей включить в расчёт. Если `ORDER BY` есть, а `ROWS BETWEEN` не указан, PostgreSQL молча использует `RANGE UNBOUNDED PRECEDING` - это частый источник неожиданных результатов.

```sql
-- Скользящая сумма за последние 3 дня включительно
SELECT
    day,
    revenue,
    SUM(revenue) OVER (ORDER BY day ROWS BETWEEN 2 PRECEDING AND CURRENT ROW) AS rolling_3d
FROM daily_sales;
```

### в) Задача, которую нельзя решить через GROUP BY

`GROUP BY` не может отфильтровать топ-N внутри группы - для этого нужен ранг, который существует только после агрегации. Оконная функция решает это в одном запросе.

```sql
-- Топ-2 товара по цене в каждой категории
SELECT category, name, price
FROM (
    SELECT
        category, name, price,
        ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) AS rn
    FROM products
) ranked
WHERE rn <= 2;
```

### г) Почему нельзя в WHERE

SQL выполняется в порядке `FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY`. Оконные функции считаются на этапе `SELECT` - после `WHERE`. В момент фильтрации их значений ещё не существует, поэтому обращение к ним в `WHERE` вызовет ошибку. Решение - обернуть в подзапрос или CTE и фильтровать снаружи.

```sql
-- Ошибка: WHERE не видит rn
SELECT *, ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) AS rn
FROM products
WHERE rn <= 2; -- ERROR

-- Правильно: фильтр снаружи
SELECT * FROM (
    SELECT *, ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) AS rn
    FROM products
) t
WHERE rn <= 2;
```

---

## Часть II - Практические задачи

### Задача 1 - Выручка по странам и категориям за 2025 год

Соединяем все четыре таблицы, фильтруем по `status = 'paid'` и году. `COUNT(DISTINCT oi.order_id)` вместо `COUNT(*)` - один заказ содержит несколько строк в `order_items`, без `DISTINCT` счётчик был бы завышен.

```sql
SELECT
    c.country,
    p.category,
    COUNT(DISTINCT oi.order_id)             AS orders_count,
    SUM(oi.quantity * oi.price_at_purchase) AS revenue
FROM customers c
JOIN orders o       ON o.customer_id = c.id
JOIN order_items oi ON oi.order_id   = o.id
JOIN products p     ON p.id          = oi.product_id
WHERE o.status = 'paid'
  AND EXTRACT(YEAR FROM o.order_date) = 2025
GROUP BY c.country, p.category
ORDER BY revenue DESC;
```

---

### Задача 2 - Клиенты с разрывом между заказами более 180 дней

`LAG(order_date)` возвращает дату предыдущего заказа того же клиента. Вычитание двух `DATE` в PostgreSQL даёт целое число дней. Оборачиваем в CTE, чтобы фильтровать по `days_gap` без повторения выражения.

```sql
WITH order_gaps AS (
    SELECT
        o.customer_id,
        c.name,
        LAG(o.order_date) OVER (PARTITION BY o.customer_id ORDER BY o.order_date) AS previous_order_date,
        o.order_date                                                                AS current_order_date,
        o.order_date - LAG(o.order_date) OVER (PARTITION BY o.customer_id ORDER BY o.order_date) AS days_gap
    FROM orders o
    JOIN customers c ON c.id = o.customer_id
)
SELECT customer_id, name, previous_order_date, current_order_date, days_gap
FROM order_gaps
WHERE days_gap > 180
ORDER BY days_gap DESC;
```

---

### Задача 3 - Топ-3 товара по выручке в каждой категории за последние 6 месяцев

Два CTE: первый агрегирует выручку по товарам, второй ранжирует и считает итог по категории в одном проходе. `NULLIF(category_total, 0)` защищает от деления на ноль. Фильтр `rank_in_category <= 3` автоматически корректен для категорий с менее чем тремя товарами.

```sql
WITH
product_revenue AS (
    SELECT
        p.category,
        p.name                                  AS product_name,
        SUM(oi.quantity * oi.price_at_purchase) AS revenue
    FROM order_items oi
    JOIN products p ON p.id = oi.product_id
    JOIN orders o   ON o.id = oi.order_id
    WHERE o.status = 'paid'
      AND o.order_date >= CURRENT_DATE - INTERVAL '6 months'
    GROUP BY p.category, p.name
),
ranked AS (
    SELECT
        category,
        product_name,
        revenue,
        ROW_NUMBER() OVER (PARTITION BY category ORDER BY revenue DESC) AS rank_in_category,
        SUM(revenue) OVER (PARTITION BY category)                       AS category_total
    FROM product_revenue
)
SELECT
    category,
    product_name,
    revenue,
    rank_in_category,
    category_total,
    ROUND(100.0 * revenue / NULLIF(category_total, 0), 2) AS share_pct
FROM ranked
WHERE rank_in_category <= 3
ORDER BY category, rank_in_category;
```

**Оптимизация для 500 млн строк:** партиционировать `order_items` по `order_date` (RANGE) - фильтр по последним 6 месяцам задействует partition pruning и читает только нужные разделы. Добавить составной индекс на `orders(order_date, status)` и писать фильтр как диапазон `order_date >= ...` без функций-обёрток - иначе индекс не используется.

