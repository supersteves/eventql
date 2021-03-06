DRAW BARCHART WITH
    ORIENTATION HORIZONTAL
    LABELS
    AXIS LEFT
    AXIS BOTTOM
    YDOMAIN 0, 20;

SELECT 'gdp per country' AS series, country AS x, gbp / 1000000 AS y, gbp / 1000 + " Billion $" as label
    FROM gdp_per_country
    LIMIT 10;
