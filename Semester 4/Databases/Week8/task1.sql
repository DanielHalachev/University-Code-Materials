USE pc
CREATE TABLE MyProduct
(
    maker NCHAR(1),
    model NCHAR(4),
    type NVARCHAR(7),
);

CREATE TABLE MyPrinter
(
    code INT,
    model NCHAR(4),
    price DECIMAL(10,2)
);

-- Insert rows into table 'MyProduct' in schema '[dbo]'
INSERT INTO [dbo].[MyProduct]
VALUES
    ('A', '1234', 'Type1'),
    ('B', '2345', 'Type1'),
    ('B', '3456', 'Type2');

-- Insert rows into table 'MyProduct' in schema '[dbo]'
INSERT INTO [dbo].[MyPrinter]
VALUES
    (2, '1234', 0.22),
    (10, '2345', 0.35),
    (5, '3456', 2.71);

ALTER TABLE MyPrinter 
ADD type NVARCHAR(6) 
    CONSTRAINT type_check 
        CHECK (type IN ('laser', 'jet', 'matrix'));


ALTER TABLE MyPrinter
    ADD color NCHAR(1) NOT NULL DEFAULT 'n'
        CONSTRAINT color_check 
            CHECK (color in ('y', 'n'));


ALTER TABLE [dbo].[MyPrinter]
    DROP COLUMN [price]

DROP TABLE MyProduct;
DROP TABLE MyPrinter;
GO