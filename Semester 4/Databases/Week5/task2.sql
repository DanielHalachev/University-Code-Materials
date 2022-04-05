--1
SELECT COUNT(CLASSES.CLASS) AS NO_Classes
FROM CLASSES
WHERE CLASSES.[TYPE]='bb';

--2
SELECT CLASSES.CLASS, AVG(CLASSES.NUMGUNS) AS avgGuns
FROM CLASSES
WHERE CLASSES.[TYPE]='bb'
GROUP BY CLASSES.CLASS;

--3
SELECT AVG(CLASSES.NUMGUNS) AS avgGuns
FROM CLASSES
WHERE CLASSES.[TYPE]='bb';

--4
SELECT CLASSES.CLASS, MIN(SHIPS.LAUNCHED), MAX(SHIPS.LAUNCHED)
FROM CLASSES, SHIPS
WHERE SHIPS.CLASS=CLASSES.CLASS
GROUP BY CLASSES.CLASS;

--5
SELECT CLASSES.CLASS, COUNT(OUTCOMES.RESULT) AS NO_Sunk
FROM CLASSES, OUTCOMES, SHIPS
WHERE OUTCOMES.RESULT='sunk' AND OUTCOMES.SHIP=SHIPS.NAME AND CLASSES.CLASS=SHIPS.CLASS
GROUP BY CLASSES.CLASS;

--6 option 1
SELECT CLASSES.CLASS, COUNT(OUTCOMES.SHIP)
FROM CLASSES, SHIPS, OUTCOMES
WHERE 
    CLASSES.CLASS=SHIPS.CLASS AND 
    OUTCOMES.RESULT='sunk' AND 
    OUTCOMES.SHIP=SHIPS.NAME 
    AND CLASSES.CLASS IN 
        (SELECT SHIPS.CLASS
        FROM CLASSES, SHIPS
        WHERE SHIPS.CLASS=CLASSES.CLASS
        GROUP BY SHIPS.CLASS 
        HAVING COUNT(CLASSES.CLASS)>2)
GROUP BY CLASSES.CLASS;

--6 option 2: JOIN CLASSES, SHIPS and OUTCOMES, GROUP BY CLASSES.CLASS AND HAVING (SELECT COUNT(1) FROM SHIPS s2 WHERE s2.CLASS=CLASSES.CLASS >2)

-- 7
SELECT CLASSES.COUNTRY, AVG(CLASSES.BORE) AS avg_bore
FROM SHIPS JOIN CLASSES ON SHIPS.CLASS=CLASSES.CLASS
GROUP BY CLASSES.COUNTRY;