--1
SELECT AVG(pc.speed) AS AvgSpeed
FROM pc

--2
SELECT product.maker, AVG(laptop.screen) AS AvgScreen
FROM product, laptop
WHERE product.model = laptop.model
GROUP BY product.maker;

--3
SELECT AVG(laptop.speed) AS AvgSpeed
FROM laptop
WHERE laptop.price > 1000;

--4
SELECT product.maker, AVG(pc.price) AS AvgPrice
FROM product, pc
WHERE product.model = pc.model
GROUP BY product.maker
HAVING product.maker='A';

--5
SELECT pr.maker, AVG(r.price)
FROM product pr, (SELECT laptop.model, laptop.price FROM laptop UNION ALL SELECT pc.model, pc.price FROM pc) r
WHERE pr.model=r.model AND pr.maker='B'
GROUP BY pr.maker;

--6
SELECT pc.speed, AVG(pc.price) AS AvgPrice
from pc
GROUP BY pc.speed;


--7
SELECT product.maker, COUNT(*) AS number_of_pc
FROM product, pc
WHERE product.model=pc.model
GROUP BY product.maker
HAVING COUNT(*)>=3;

--8
SELECT product.maker, pc.price
FROM product, pc
WHERE product.model=pc.model AND pc.price=(SELECT MAX(pc1.price) FROM pc pc1);

--9
SELECT pc.speed, AVG(pc.price) AS AvgPrice
FROM pc
GROUP BY pc.speed
HAVING pc.speed > 800

-- 10
SELECT product.maker, AVG(pc.hd) AS AvgHDD
FROM product, pc
WHERE product.model=pc.model AND product.maker IN (SELECT product.maker FROM product, printer WHERE product.model=printer.model)
GROUP BY product.maker;
