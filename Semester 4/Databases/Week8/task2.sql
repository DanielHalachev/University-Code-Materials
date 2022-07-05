-- Create a new database called 'Facebook'
-- Connect to the 'master' database to run this snippet
USE master
GO
-- Create the new database if it does not exist already
IF NOT EXISTS (
    SELECT [name]
        FROM sys.databases
        WHERE [name] = N'Facebook'
)
CREATE DATABASE Facebook

USE Facebook

IF OBJECT_ID('[dbo].[Users]', 'U') IS NOT NULL
DROP TABLE [dbo].[Users]
GO
-- CREATE TABLE [dbo].[Users]
-- (
--     [Id] INT NOT NULL, 
--     [email] NVARCHAR(50) NOT NULL,
--     [password] NVARCHAR(50) NOT NULL,
--     [regdate] DATETIME NOT NULL,
--     CONSTRAINT pk_usrs PRIMARY KEY ([id])
-- )
CREATE TABLE [dbo].[Users]
(
    [Id] UNIQUEIDENTIFIER NOT NULL PRIMARY KEY, 
    [email] NVARCHAR(50) NOT NULL,
    [password] NVARCHAR(50) NOT NULL,
    [regdate] DATETIME NOT NULL
)
GO

IF OBJECT_ID('[dbo].[Friends]', 'U') IS NOT NULL
DROP TABLE [dbo].[Friends]
GO
CREATE TABLE [dbo].[Friends]
(
    [Friend1] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_fr1 REFERENCES [dbo].[Users]([id]),
    [Friend2] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_fr2 REFERENCES [dbo].[Users]([id]),
    CONSTRAINT pk_fr PRIMARY KEY ([Friend1], [Friend2])
);
GO

IF OBJECT_ID('[dbo].[Walls]', 'U') IS NOT NULL
DROP TABLE [dbo].[Walls]
GO
CREATE TABLE [dbo].[Walls]
(
    [User1] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_walls1 REFERENCES [dbo].[Users]([id]),
    [Sender] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_walls2 REFERENCES [dbo].[Users]([id]),
    [Text] NVARCHAR(100) NOT NULL,
    [Date] DATETIME NOT NULL,
    CONSTRAINT pk_walls PRIMARY KEY (User1, Sender)
);
GO

IF OBJECT_ID('[dbo].[Groups]', 'U') IS NOT NULL
DROP TABLE [dbo].[Groups]
GO
CREATE TABLE [dbo].[Groups]
(
    [Id] UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
    [Name] NVARCHAR(50) NOT NULL,
    [Description] NVARCHAR(50) NOT NULL
);
GO

-- Create a new table called '[GroupMembers]' in schema '[dbo]'
-- Drop the table if it already exists
IF OBJECT_ID('[dbo].[GroupMembers]', 'U') IS NOT NULL
DROP TABLE [dbo].[GroupMembers]
GO
-- Create the table in the specified schema
CREATE TABLE [dbo].[GroupMembers]
(
    [GroupID] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_grp1 REFERENCES [dbo].[Groups]([id]),
    [UserID] UNIQUEIDENTIFIER NOT NULL CONSTRAINT fk_grp2 REFERENCES [dbo].[Users]([id]),
    CONSTRAINT pk_grp PRIMARY KEY ([GroupID], [UserID])
);
GO

-- DROP TABLE Walls;
-- DROP TABLE Friends;
-- DROP TABLE GroupMembers;
-- DROP TABLE Groups;
-- DROP TABLE Users;
