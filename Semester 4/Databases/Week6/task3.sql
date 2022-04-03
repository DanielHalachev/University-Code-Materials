-- --1
-- SELECT l.model, l.code, l.screen
-- FROM laptop l, laptop l2
-- WHERE l.model=l2.model AND ((l.screen=15 AND l2.screen=11) OR (l.screen=11 AND l2.screen=15))

-- --2
-- SELECT DISTINCT pc.model
-- FROM pc pc, product p
-- WHERE pc.model = p.model AND pc.price <(SELECT MIN(laptop.price) FROM laptop, product pr WHERE laptop.model = pr.model AND pr.maker = p.maker)

-- --3
-- SELECT pc1.model, pr1.maker, AVG(pc1.price)
-- FROM pc pc1, product pr1
-- WHERE pc1.model=pr1.model
-- GROUP BY pc1.model, pr1.maker
-- HAVING avg(pc1.price) < (SELECT MIN(laptop.price) FROM laptop, product pr2 WHERE laptop.model=pr2.model and pr1.maker=pr2.maker);

--4
SELECT pc1.code, pr1.maker, COUNT(pc2.code)
FROM pc pc1, pc pc2, product pr1 
WHERE pc1.model=pr1.model AND pc2.model=pr1.model AND pc1.price<=pc2.price
GROUP BY pc1.code, pr1.maker 
