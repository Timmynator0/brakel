USE [master]
GO
/****** Object:  Database [Brakel]    Script Date: 4-7-2013 11:01:14 ******/
CREATE DATABASE [Brakel]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Brakel', FILENAME = N'c:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\Brakel.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'Brakel_log', FILENAME = N'c:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\Brakel_log.ldf' , SIZE = 1536KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [Brakel] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Brakel].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Brakel] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Brakel] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Brakel] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Brakel] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Brakel] SET ARITHABORT OFF 
GO
ALTER DATABASE [Brakel] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Brakel] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [Brakel] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Brakel] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Brakel] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Brakel] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Brakel] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Brakel] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Brakel] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Brakel] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Brakel] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Brakel] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Brakel] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Brakel] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Brakel] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Brakel] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Brakel] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Brakel] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Brakel] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [Brakel] SET  MULTI_USER 
GO
ALTER DATABASE [Brakel] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Brakel] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Brakel] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Brakel] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
USE [Brakel]
GO
/****** Object:  User [brakel_usr]    Script Date: 4-7-2013 11:01:14 ******/
CREATE USER [brakel_usr] FOR LOGIN [brakel_usr] WITH DEFAULT_SCHEMA=[dbo]
GO
ALTER ROLE [db_datareader] ADD MEMBER [brakel_usr]
GO
ALTER ROLE [db_datawriter] ADD MEMBER [brakel_usr]
GO
/****** Object:  Table [dbo].[DataPoint]    Script Date: 4-7-2013 11:01:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DataPoint](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Time] [bigint] NOT NULL,
	[Temperature] [int] NULL,
	[CO2] [int] NULL,
	[Humidity] [int] NULL,
	[Light] [int] NULL,
	[NodeAdress] [varchar](max) NOT NULL,
 CONSTRAINT [PK_DataPoint] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Node]    Script Date: 4-7-2013 11:01:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Node](
	[NodeAdress] [varchar](50) NOT NULL,
	[Location] [varchar](50) NULL,
	[Type] [smallint] NOT NULL,
	[ObjectActive] [bit] NULL,
 CONSTRAINT [PK_Node] PRIMARY KEY CLUSTERED 
(
	[NodeAdress] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'table containing all the nodes' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Node'
GO
USE [master]
GO
ALTER DATABASE [Brakel] SET  READ_WRITE 
GO
