-- Create a new database called 'Flights'
-- Connect to the 'master' database to run this snippet

-- Create the new database if it does not exist already
IF NOT EXISTS (
    SELECT [name]
FROM sys.databases
WHERE [name] = N'Flights'
)
CREATE DATABASE Flights
GO
Use Flights
GO
-- Create a new table called '[AIRLINE]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[AIRLINE]', 'U') IS NOT NULL
DROP TABLE [dbo].[AIRLINE]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[AIRLINE]
(
    [Code] VARCHAR(10) NOT NULL PRIMARY KEY,
    [Name] NVARCHAR(50) NOT NULL UNIQUE,
    [Country] NVARCHAR(50) NOT NULL
    -- CONSTRAINT unique_AIRLINE_name UNIQUE([Name])
);
GO

-- Create a new table called '[AIRPLANE]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[AIRPLANE]', 'U') IS NOT NULL
DROP TABLE [dbo].[AIRPLANE]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[AIRPLANE]
(
    [Code] VARCHAR(10) NOT NULL PRIMARY KEY,
    [Type] NVARCHAR(50) NOT NULL,
    [Seats] INT NOT NULL CHECK ([Seats] > 0),
    [Year] INT NOT NULL CHECK ([Year]>1900)
);
GO

-- Create a new table called '[AGENCY]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[AGENCY]', 'U') IS NOT NULL
DROP TABLE [dbo].[AGENCY]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[AGENCY]
(
    [Name] NVARCHAR(30) NOT NULL PRIMARY KEY,
    [Country] NVARCHAR(50) NOT NULL,
    [City] NVARCHAR(50) NOT NULL,
    [Phone] VARCHAR(20)
);
GO

-- Create a new table called '[CUSTOMER]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[CUSTOMER]', 'U') IS NOT NULL
DROP TABLE [dbo].[CUSTOMER]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[CUSTOMER]
(
    [Id] INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
    [FName] NVARCHAR(50) NOT NULL,
    [LName] NVARCHAR(50) NOT NULL,
    [Email] NVARCHAR(50) NOT NULL CHECK ([Email] LIKE '%_@%__.%__')
)
SET IDENTITY_INSERT [dbo].[CUSTOMER] ON;
GO

-- Create a new table called '[dbo]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[AIRPORT]', 'U') IS NOT NULL
DROP TABLE [dbo].[AIRPORT]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[AIRPORT]
(
    [Code] VARCHAR(10) NOT NULL PRIMARY KEY,
    [Name] NVARCHAR(50) NOT NULL,
    [Country] NVARCHAR(50) NOT NULL,
    [City] NVARCHAR(50) NOT NULL,
    CONSTRAINT unique_city_country_airprt UNIQUE([Country], [Name])
    -- Unique combination Country-Name
);
GO

-- Create a new table called '[FLIGHT]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[FLIGHT]', 'U') IS NOT NULL
DROP TABLE [dbo].[FLIGHT]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[FLIGHT]
(
    [FNumber] VARCHAR(10) PRIMARY KEY,
    [AIRLINEOperator] VARCHAR(10) NOT NULL CONSTRAINT fk_oper REFERENCES [dbo].[AIRLINE]([Code]),
    [Depdbo] VARCHAR(10) NOT NULL CONSTRAINT fk_airprt1 REFERENCES [dbo].[dbo]([Code]),
    [Arrdbo] VARCHAR(10) NOT NULL CONSTRAINT fk_airprt2 REFERENCES [dbo].[dbo]([Code]),
    [FlightTime] DATETIME NOT NULL,
    [FlightDuration] INT NOT NULL CHECK ([FlightDuration] > 0),
    [AIRPLANE] VARCHAR(10) NOT NULL CONSTRAINT fk_plane REFERENCES [dbo].[AIRPLANE]([Code])
);
GO

-- Create a new table called '[BOOKING]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[BOOKING]', 'U') IS NOT NULL
DROP TABLE [dbo].[BOOKING]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[BOOKING]
(
    [Code] VARCHAR(10) NOT NULL PRIMARY KEY,
    [AGENCY] NVARCHAR(30) NOT NULL CONSTRAINT fk_AGENCY REFERENCES [dbo].[AGENCY]([Name]),
    [AIRLINECode] VARCHAR(10) NOT NULL CONSTRAINT fk_AIRLINE REFERENCES [dbo].[AIRLINE]([Code]),
    [FlightNumber] VARCHAR(10) NOT NULL CONSTRAINT fk_fl_num REFERENCES [dbo].[FLIGHT]([FNumber]),
    [CUSTOMERID] INT NOT NULL CONSTRAINT fk_custm REFERENCES [dbo].[CUSTOMER]([id]),
    [BOOKINGDate] DATE NOT NULL,
    [FlightDate] DATE NOT NULL,
    [Price] DECIMAL(19,4) NOT NULL CHECK ([Price] > 0 ),
    -- MONEY NOT NULL,
    [Status] BINARY NOT NULL DEFAULT 0,
    CONSTRAINT corr_dates CHECK ([FlightDate]>=[BOOKINGDate])
);
GO

-- TESTING
INSERT INTO [dbo].[AIRLINE]
VALUES
    ('AZ', 'Alitalia', 'Italy'),
    ('BA', 'British Airways', 'United Kingdom'),
    ('LH', 'Lufthansa', 'Germany'),
    ('SR', 'Swissair', 'Switzerland'),
    ('FB', 'Bulgaria Air', 'Bulgaria'),
    ('AF', 'Air France', 'France'),
    ('TK', 'Turkish AIRLINEs', 'Turkey'),
    ('AA', 'American AIRLINEs', 'United States');
INSERT INTO dbo.[AIRPORT]
VALUES
    ('SOF', 'Sofia International', 'Bulgaria', 'Sofia'),
    ('CDG', 'Charles De Gaulle', 'France', 'Paris'),
    ('ORY', 'Orly', 'France', 'Paris'),
    ('LBG', 'Le Bourget', 'France', 'Paris'),
    ('JFK', 'John F Kennedy International', 'United States', 'New York'),
    ('ORD', 'Chicago O''Hare International', 'United States', 'Chicago'),
    ('FCO', 'Leonardo da Vinci International', 'Italy', 'Rome'),
    ('LHR', 'London Heathrow', 'United Kingdom', 'London');
INSERT INTO [dbo].[AIRPLANE]
VALUES
    ('319', 'Airbus A319', 150, 1993),
    ('320', 'Airbus A320', 280, 1984),
    ('321', 'Airbus A321', 150, 1989),
    ('100', 'Fokker 100', 80, 1991),
    ('738', 'Boeing 737-800', 90, 1997),
    ('735', 'Boeing 737-800', 90, 1995);
INSERT INTO [dbo].[FLIGHT]
VALUES
    ('FB1363', 'AZ', 'SOF', 'ORY', '12:45', 100, '738'),
    ('FB1364', 'AZ', 'CDG', 'SOF', '10:00', 120, '321'),
    ('SU2060', 'AZ', 'LBG', 'SOF', '11:10', 110, '738'),
    ('SU2061', 'TK', 'SOF', 'JFK', '13:00', 110, '320'),
    ('FB363', 'FB', 'SOF', 'ORD', '15:10', 110, '738'),
    ('FB364', 'FB', 'LHR', 'SOF', '21:05', 120, '738');
INSERT INTO [dbo].[CUSTOMER]
    (id, FName, LName, Email)
VALUES
    (1, 'Petar', 'Milenov', 'petter@mail.com'),
    (2, 'Dimitar', 'Petrov', 'petrov@mail.com'),
    (3, 'Ivan', 'Ivanov', 'ivanov@mail.com'),
    (4, 'Petar', 'Slavov', 'slavov@mail.com'),
    (5, 'Bogdan', 'Bobov', 'bobov@mail.com');
INSERT INTO [dbo].[AGENCY]
VALUES
    ('Travel One', 'Bulgaria', 'Sofia', '0783482233'),
    ('Travel Two', 'Bulgaria', 'Plovdiv', '02882234'),
    ('Travel Tour', 'Bulgaria', 'Sofia', NULL),
    ('Aerotravel', 'Bulgaria', 'Varna', '02884233');
INSERT INTO [dbo].[BOOKING]
VALUES
    ('YN298P', 'Travel One', 'FB', 'FB1363', 1, '2013-11-18', '2013-12-25', 300, 0),
    ('YA298P', 'Travel Two', 'FB', 'FB1364', 2, '2013-12-18', '2013-12-25', 300, 1),
    ('YB298P', 'Travel Tour', 'FB', 'SU2060', 3, '2014-01-18', '2014-02-25', 400, 0),
    ('YC298P', 'Travel One', 'FB', 'SU2061', 4, '2014-11-11', '2014-11-25', 350, 0),
    ('YD298P', 'Travel Tour', 'FB', 'FB363', 1, '2013-11-03', '2013-12-20', 250, 1),
    ('YE298P', 'Aerotravel', 'FB', 'FB364', 2, '2013-11-07', '2013-12-21', 150, 0);


-- -- DELETING
-- -- Drop a table called 'BOOKING' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[BOOKING]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[BOOKING]
-- GO

-- -- Drop a table called 'FLIGHT' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[FLIGHT]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[FLIGHT]
-- GO

-- -- Drop a table called 'AIRPORT' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[AIRPORT]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[AIRPORT]
-- GO

-- -- Drop a table called 'CUSTOMER' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[CUSTOMER]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[CUSTOMER]
-- GO

-- -- Drop a table called 'AGENCY' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[AGENCY]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[AGENCY]
-- GO  

-- -- Drop a table called 'AIRLINE' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[AIRLINE]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[AIRLINE]
-- GO  

-- -- Drop a table called 'AIRPLANE' in schema 'dbo'
-- -- Drop the table if it already exists
-- IF OBJECT_ID('[dbo].[AIRPLANE]', 'U') IS NOT NULL
-- DROP TABLE [dbo].[AIRPLANE]
-- GO

-- -- This thingy kills all DB processes
-- DECLARE @DatabaseName nvarchar(50)
-- SET @DatabaseName = N'Flights'

-- DECLARE @SQL varchar(max)

-- SELECT @SQL = COALESCE(@SQL,'') + 'Kill ' + Convert(varchar, SPId) + ';'
-- FROM MASTER..SysProcesses
-- WHERE DBId = DB_ID(@DatabaseName) AND SPId <> @@SPId

-- --SELECT @SQL 
-- EXEC(@SQL)

-- DROP DATABASE Flights
-- GO
