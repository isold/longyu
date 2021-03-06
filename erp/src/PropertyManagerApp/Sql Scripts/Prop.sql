USE [master]
GO
/****** Object:  Database [Prop]    Script Date: 2013/1/24 11:58:32 ******/
CREATE DATABASE [Prop]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Prop', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.PROPMGR\MSSQL\DATA\Prop.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'Prop_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.PROPMGR\MSSQL\DATA\Prop_log.ldf' , SIZE = 2560KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [Prop] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Prop].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Prop] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Prop] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Prop] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Prop] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Prop] SET ARITHABORT OFF 
GO
ALTER DATABASE [Prop] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Prop] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [Prop] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Prop] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Prop] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Prop] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Prop] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Prop] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Prop] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Prop] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Prop] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Prop] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Prop] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Prop] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Prop] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Prop] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Prop] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Prop] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Prop] SET RECOVERY FULL 
GO
ALTER DATABASE [Prop] SET  MULTI_USER 
GO
ALTER DATABASE [Prop] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Prop] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Prop] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Prop] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
EXEC sys.sp_db_vardecimal_storage_format N'Prop', N'ON'
GO
USE [Prop]
GO
/****** Object:  StoredProcedure [dbo].[_Log]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[_Log] 
	@Lvl TINYINT,
	@OpId INT,
	@Kword VARCHAR(64),
	@Txt VARCHAR(1024)
AS
BEGIN
	INSERT INTO [dbo.Log](Lvl,OpId,Kword,Txt) VALUES (@Lvl,@OpId,@Kword,@Txt)
END

GO
/****** Object:  StoredProcedure [dbo].[_SpoooResetAllooo]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[_SpoooResetAllooo]
	
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @AdminGroupId INT
	DECLARE @OpId INT

	TRUNCATE TABLE Log
	TRUNCATE TABLE UserGroup
	TRUNCATE TABLE UserGroupOp
	TRUNCATE TABLE UserInfo
	TRUNCATE TABLE UserOp 
	 

	INSERT INTO UserGroup (Name,Intro,Parent) VALUES ('超级管理员','该分组为系统最高级别组',-1)
	SELECT @AdminGroupId = @@IDENTITY

	INSERT INTO UserInfo (Name,Pwd,GroupId) VALUES ('admin','111111',@AdminGroupId)

	INSERT INTO UserOp (Id,Name,Intro) VALUES (0,'分组管理','建立/修改/删除 分组操作')
	INSERT INTO UserGroupOp (GroupId,OpId) VALUES (@AdminGroupId,0)
	INSERT INTO UserOp (Id,Name,Intro) VALUES (1,'用户管理','建立/修改/删除 用户操作')
	INSERT INTO UserGroupOp (GroupId,OpId) VALUES (@AdminGroupId,1)

END

GO
/****** Object:  StoredProcedure [dbo].[_TestGroupOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
 
CREATE PROCEDURE [dbo].[_TestGroupOp]
	@UserId INT,
	@GroupId INT,
	@ChildOp BIT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @UserGroupId INT
	DECLARE @ParentGroupId INT
	
	SELECT @UserGroupId=GroupId FROM UserInfo WHERE Id=@UserId
	IF @UserGroupId IS NULL
		RETURN -1;
	IF NOT EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@UserGroupId AND OpId=0)
		RETURN -2;
		
	IF @ChildOp=1 AND @UserGroupId=@GroupId
		RETURN @UserGroupId

LOOPBEGIN: 
	SELECT @ParentGroupId=Parent FROM UserGroup WHERE Id=@GroupId
	IF @ParentGroupId IS NULL OR @ParentGroupId=-1
		RETURN -3;

	IF @ParentGroupId=@UserGroupId
		RETURN @UserGroupId;
	SET @GroupId = @ParentGroupId
	GOTO LOOPBEGIN
END

GO
/****** Object:  StoredProcedure [dbo].[_TestGroupUser]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
 
CREATE PROCEDURE [dbo].[_TestGroupUser]
	@UserId INT,
	@GroupId INT,
	@ChildOp BIT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @UserGroupId INT
	DECLARE @ParentGroupId INT
	
	SELECT @UserGroupId=GroupId FROM UserInfo WHERE Id=@UserId
	IF @UserGroupId IS NULL
		RETURN -1;
	IF NOT EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@UserGroupId AND OpId=1)
		RETURN -2;
		
	IF @ChildOp=1 AND @UserGroupId=@GroupId
		RETURN @UserGroupId

LOOPBEGIN: 
	SELECT @ParentGroupId=Parent FROM UserGroup WHERE Id=@GroupId
	IF @ParentGroupId IS NULL OR @ParentGroupId=-1
		RETURN -3;

	IF @ParentGroupId=@UserGroupId
		RETURN @UserGroupId;
	SET @GroupId = @ParentGroupId
	GOTO LOOPBEGIN
END

GO
/****** Object:  StoredProcedure [dbo].[RRGetGroupOps]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RRGetGroupOps]
		@UserId INT,
		@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON; 
	DECLARE @Opable INT 
	DECLARE @GroupId INT
	DECLARE @TreeLvl INT
	DECLARE @ParentTreeLvl INT
	
	
	SELECT @GroupId=GroupId FROM UserInfo WHERE Id=@UserId;
	IF @GroupId IS NULL
		BEGIN
			SELECT @ErrDesc='请求用户不存在';
			RETURN -1;
		END

	SELECT @Opable = 0 
	SELECT @Opable=@Opable+1 IF EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@GroupId AND OpId=1)
	SELECT @Opable=@Opable+2 IF EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@GroupId AND OpId=0)

	IF @Opable=0
		BEGIN
			SELECT @ErrDesc='用户无权进行此操作';
			RETURN -2;
		END

	SELECT @TreeLvl = 0
	CREATE TABLE #TmpTable (Id INT,TLvl INT)
	INSERT #TmpTable SELECT @GroupId,0

	WHILE @@ROWCOUNT > 0
		BEGIN
			SET @ParentTreeLvl = @TreeLvl
			SET @TreeLvl = @TreeLvl + 1
			INSERT INTO #TmpTable SELECT UserGroup.Id,@TreeLvl FROM UserGroup,#TmpTable AS Tmp 
				WHERE UserGroup.Parent=Tmp.Id AND Tmp.TLvl=@ParentTreeLvl
		END

	SELECT UserGroup.Id AS GroupId, UserGroup.Name AS GroupName, UserGroup.Intro As GroupIntro,
			 UserGroup.Parent AS GroupParent,UserGroupOp.OpId AS OpId, UserOp.Name AS OpName,UserOp.Intro AS OpIntro 
			FROM UserGroup INNER JOIN #TmpTable AS Tmp ON UserGroup.Id=Tmp.Id LEFT OUTER JOIN UserGroupOp  ON UserGroup.Id=UserGroupOp.GroupId
			 LEFT OUTER JOIN UserOp ON UserGroupOp.OpId=UserOp.Id

	RETURN @Opable
		
END

GO
/****** Object:  StoredProcedure [dbo].[RRGetOps]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RRGetOps]
		@UserId INT,
		@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	 
	IF NOT EXISTS(SELECT * FROM UserInfo WHERE Id=@UserId AND GroupId=1)
		BEGIN
			SELECT @ErrDesc='操作用户无权进行操作管理';
			RETURN -1;
		END
 

	SELECT * FROM UserOp
	RETURN @@ROWCOUNT
		
END

GO
/****** Object:  StoredProcedure [dbo].[RRGetUserOps]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[RRGetUserOps]
	@UserId INT
AS
BEGIN 
	DECLARE @GroupId INT
	SELECT @GroupId=GroupId FROM UserInfo WHERE Id=@UserId
 	IF @GroupId IS NOT NULL
		SELECT UserOp.Id AS OpId,UserOp.Name AS OpName,UserOP.Intro AS OpIntro FROM UserGroupOp,UserOp 
			WHERE UserGroupOp.GroupId=@GroupId AND UserGroupOp.OpId=UserOp.Id
END

GO
/****** Object:  StoredProcedure [dbo].[RRGetUsers]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
 
CREATE PROCEDURE [dbo].[RRGetUsers]
	@UserId INT,
	@ErrDesc VARCHAR(128) OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SET NOCOUNT ON; 
	DECLARE @GroupId INT
	DECLARE @TreeLvl INT
	DECLARE @ParentTreeLvl INT
	
	
	SELECT @GroupId=GroupId FROM UserInfo WHERE Id=@UserId
	IF @GroupId IS NULL
		BEGIN
			SELECT @ErrDesc='操作用户不存在'
			RETURN -1;
		END
	IF NOT EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@GroupId AND OpId=1)
		BEGIN
			SELECT @ErrDesc='操作用户无权进行用户管理';
			RETURN -2;
		END
	

		 
	SELECT @TreeLvl = 0
	CREATE TABLE #TmpTable (Id INT,TLvl INT)
	INSERT #TmpTable SELECT @GroupId,0

	WHILE @@ROWCOUNT > 0
		BEGIN
			SET @ParentTreeLvl = @TreeLvl
			SET @TreeLvl = @TreeLvl + 1
			INSERT INTO #TmpTable SELECT UserGroup.Id,@TreeLvl FROM UserGroup,#TmpTable AS Tmp 
				WHERE UserGroup.Parent=Tmp.Id AND Tmp.TLvl=@ParentTreeLvl
		END
	DELETE FROM #TmpTable WHERE Id=@GroupId
	SELECT UserInfo.Id AS UserId,UserInfo.Name AS UserName,UserInfo.GroupId AS UserGroup,UserGroup.Name AS GroupName FROM UserInfo,UserGroup
		WHERE UserInfo.GroupId=UserGroup.Id AND UserInfo.GroupId IN (SELECT Tmp.Id FROM #TmpTable AS Tmp)
		 
	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVAddGroup]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

 

CREATE PROCEDURE [dbo].[RVAddGroup]
	@UserId INT,
	@GroupId INT,
	@Name VARCHAR(32),
	@Intro VARCHAR(256),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	 
	DECLARE @UserGroupId INT
	 
	IF @Name=''
		BEGIN
			SELECT @ErrDesc='分组名称不能为空';
			RETURN -1;	
		END

	IF EXISTS (SELECT * FROM UserGroup WHERE Name=@Name)
		BEGIN
			SELECT @ErrDesc='同名分组已经存在';
			RETURN -2;	
		END		

	EXEC @UserGroupId=_TestGroupOp @UserId,@GroupId,1
	IF @UserGroupId<0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行该分组管理';
			RETURN -3;
		END

	 
	INSERT INTO UserGroup(Name,Intro,Parent) VALUES(@Name,@Intro,@GroupId);
	RETURN @@IDENTITY
END

GO
/****** Object:  StoredProcedure [dbo].[RVAddGroupOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVAddGroupOp]
		@UserId INT,
		@GroupId INT,
		@OpId INT,
		@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	
	DECLARE @UserGroupId INT 
	DECLARE @ParentGroupId INT

	EXEC @UserGroupId=_TestGroupOp @UserId,@GroupId,1
	IF @UserGroupId<0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行该分组管理';
			RETURN -1;
		END

	SELECT @ParentGroupId=Parent FROM UserGroup WHERE Id=@GroupId
	IF NOT EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@ParentGroupId AND OpId=@OpId)
		BEGIN
			SELECT @ErrDesc='不能添加上级组中不存在的操作';
			RETURN -2;
		END

	IF EXISTS (SELECT * FROM UserGroupOp WHERE GroupId=@GroupId AND OpId=@OpId)
		BEGIN
			SELECT @ErrDesc='分组中已经存在该操作';
			RETURN -3;
		END

		 
	INSERT INTO UserGroupOp(GroupId,OpId) VALUES(@GroupId,@OpId)
	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVAddOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVAddOp]
	@UserId INT,
	@Id INT,
	@Name VARCHAR(32),
	@Intro VARCHAR(256),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @GroupId INT 

	IF @Name=''
		BEGIN
			SELECT @ErrDesc='操作名称不能为空';
			RETURN -1;	
		END

	IF NOT EXISTS(SELECT * FROM UserInfo WHERE Id=@UserId AND GroupId=1)
		BEGIN
			SELECT @ErrDesc='操作用户无权进行操作管理';
			RETURN -2;
		END
	
	IF EXISTS (SELECT * FROM UserOp WHERE Id=@Id)
		BEGIN
			SELECT @ErrDesc='同标识操作已经存在';
			RETURN -3;	
		END

	INSERT INTO UserOp(Id,Name,Intro) VALUES(@Id,@Name,@Intro);
	RETURN @@ROWCOUNT


END

GO
/****** Object:  StoredProcedure [dbo].[RVAddUser]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVAddUser] 
	@UserId INT,
	@Name VARCHAR(32),
	@Pwd VARCHAR(32),
	@GroupId INT,
	@ErrDesc VARCHAR(128) OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @UserGroupId INT

	IF LEN(@Name) < 3
		BEGIN
			SELECT @ErrDesc='用户名长度必须大于 2';
			RETURN -1;
		END
	
	IF LEN(@Pwd) < 6
		BEGIN
			SELECT @ErrDesc='密码长度必须大于 5';
			RETURN -2			
		END
	
	IF (EXISTS (SELECT * FROM UserInfo WHERE Name=@Name))
		BEGIN
			SELECT @ErrDesc='同名用户已存在';
			RETURN -3;
		END

	EXEC @UserGroupId = _TestGroupUser @UserId,@GroupId,1
	IF @UserGroupId < 0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行此操作';
			RETURN -4;
		END


	INSERT INTO UserInfo(Name,Pwd,GroupId) VALUES(@Name,@Pwd,@GroupId);
	RETURN @@IDENTITY

END
GO
/****** Object:  StoredProcedure [dbo].[RVCheckUser]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVCheckUser]
	@Name VARCHAR(32),
	@Pwd VARCHAR(32)
AS
BEGIN 
	SET NOCOUNT ON

	DECLARE @Id INT
	 
	SELECT @Id=Id FROM UserInfo WHERE Name=@Name AND Pwd=@Pwd;
	
	IF @Id IS NULL
		SELECT @Id = -1;
	RETURN @Id;
END

GO
/****** Object:  StoredProcedure [dbo].[RVDelGroup]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RVDelGroup]
	@UserId INT,
	@GroupId INT,
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @Groupable INT
	DECLARE @TreeLvl INT
	DECLARE @ParentTreeLvl INT

	EXEC @Groupable=_TestGroupOp @UserId,@GroupId,1
	IF @Groupable<0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行该分组管理';
			RETURN -1;
		END

	SELECT @TreeLvl = 0
	CREATE TABLE #TmpTable (Id INT,TLvl INT)
	INSERT #TmpTable SELECT @GroupId,0

	WHILE @@ROWCOUNT > 0
		BEGIN
			SET @ParentTreeLvl = @TreeLvl
			SET @TreeLvl = @TreeLvl + 1
			INSERT INTO #TmpTable SELECT UserGroup.Id,@TreeLvl FROM UserGroup,#TmpTable AS Tmp 
				WHERE UserGroup.Parent=Tmp.Id AND Tmp.TLvl=@ParentTreeLvl
		END 
 
	DELETE FROM UserGroupOp WHERE UserGroupOp.GroupId IN (SELECT Tmp.Id FROM #TmpTable AS Tmp)
	DELETE FROM UserGroup WHERE UserGroup.Id IN (SELECT Tmp.Id FROM #TmpTable AS Tmp)

	RETURN @@ROWCOUNT 
END

GO
/****** Object:  StoredProcedure [dbo].[RVDelGroupOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVDelGroupOp]
		@UserId INT,
		@GroupId INT,
		@OpId INT,
		@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	
	DECLARE @Groupable INT
	DECLARE @TreeLvl INT
	DECLARE @ParentTreeLvl INT

	EXEC @Groupable=_TestGroupOp @UserId,@GroupId,1
	IF @Groupable<0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行该分组管理';
			RETURN -1;
		END

	SELECT @TreeLvl = 0
	CREATE TABLE #TmpTable (Id INT,TLvl INT)
	INSERT #TmpTable SELECT @GroupId,0

	WHILE @@ROWCOUNT > 0
		BEGIN
			SET @ParentTreeLvl = @TreeLvl
			SET @TreeLvl = @TreeLvl + 1
			INSERT INTO #TmpTable SELECT UserGroup.Id,@TreeLvl FROM UserGroup,#TmpTable AS Tmp 
				WHERE UserGroup.Parent=Tmp.Id AND Tmp.TLvl=@ParentTreeLvl
		END 
 
	DELETE FROM UserGroupOp WHERE UserGroupOp.OpId=@OpId AND UserGroupOp.GroupId IN (SELECT Tmp.Id FROM #TmpTable AS Tmp)
	 
	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVDelOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RVDelOp]
	@UserId INT,
	@Id INT,
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
 
	IF NOT EXISTS(SELECT * FROM UserInfo WHERE Id=@UserId AND GroupId=1)
		BEGIN
			SELECT @ErrDesc='操作用户无权进行操作管理';
			RETURN -2;
		END

	DELETE FROM UserOp WHERE Id=@Id
 	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVDelUser]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[RVDelUser] 
	@UserId INT,
	@OpedId INT,
	@ErrDesc VARCHAR(128) OUTPUT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @UserGroupId INT
	DECLARE @OpedUserGroupId INT

	SELECT @OpedUserGroupId=GroupId FROM UserInfo WHERE Id=@OpedId
	IF @OpedUserGroupId IS NULL
		BEGIN
			SELECT @ErrDesc='删除的用户不存在';
			RETURN -1;
		END

	EXEC @UserGroupId = _TestGroupUser @UserId,@OpedUserGroupId,1
	IF @UserGroupId < 0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行此操作';
			RETURN -2;
		END

	DELETE FROM UserInfo WHERE Id=@OpedId
	RETURN @@ROWCOUNT

END
GO
/****** Object:  StoredProcedure [dbo].[RVUpdateGroup]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
 
CREATE PROCEDURE [dbo].[RVUpdateGroup]
	@UserId INT,
	@GroupId INT,
	@Name VARCHAR(32),
	@Intro VARCHAR(256),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
 
	SET NOCOUNT ON;
	DECLARE @MgrLvl INT
	DECLARE @UserGroupId BIT
	DECLARE @NameId INT
	 
	 
	IF @Name=''
		BEGIN
			SELECT @ErrDesc='分组名称不能为空';
			RETURN -1;	
		END

	IF EXISTS (SELECT * FROM UserGroup WHERE Id<>@GroupId AND Name=@Name)
		BEGIN
			SELECT @ErrDesc='同名分组已经存在';
			RETURN -2;	
		END		

	EXEC @UserGroupId=_TestGroupOp @UserId,@GroupId,0
	IF @UserGroupId<0
		BEGIN
			SELECT @ErrDesc='操作用户无权进行该分组管理';
			RETURN -3;
		END

	UPDATE UserGroup SET Name=@Name,Intro=@Intro WHERE Id=@GroupId
	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVUpdateGroupUser]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RVUpdateGroupUser]
	@UserId INT,
	@OpedId INT,
	@GroupId INT,
	@Password VARCHAR(32),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @OpedGroupId INT
	DECLARE @UserGroupId INT

	EXEC @UserGroupId=_TestGroupUser @UserId,@GroupId,1
	IF @UserGroupId < 0
		BEGIN
			SELECT @ErrDesc='操作用户无权对该组进行操作'
			RETURN -2
		END

	SELECT @OpedGroupId=GroupId FROM UserInfo WHERE Id=@OpedId
	IF @OpedGroupId IS NULL
		BEGIN
			SELECT @ErrDesc='被操作用户不存在'
			RETURN -1
		END

	EXEC @UserGroupId=_TestGroupUser @UserId,@OpedGroupId,1
	IF @UserGroupId < 0
		BEGIN
			SELECT @ErrDesc='操作用户无权对用户进行操作'
			RETURN -2
		END

	IF @Password <> ''
		UPDATE UserInfo SET Pwd=@Password WHERE Id=@OpedId
	IF @GroupId <> @OpedGroupId
		UPDATE UserInfo SET GroupId=@GroupId WHERE Id=@OpedId

	RETURN 0
END

GO
/****** Object:  StoredProcedure [dbo].[RVUpdateOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
 
CREATE PROCEDURE [dbo].[RVUpdateOp]
	@UserId INT,
	@OldOpId INT,
	@Id INT,
	@Name VARCHAR(32),
	@Intro VARCHAR(256),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN
 
	SET NOCOUNT ON;  

	IF @Name=''
		BEGIN
			SELECT @ErrDesc='操作名称不能为空';
			RETURN -1;	
		END

	IF NOT EXISTS(SELECT * FROM UserInfo WHERE Id=@UserId AND GroupId=1)
		BEGIN
			SELECT @ErrDesc='操作用户无权进行操作管理';
			RETURN -2;
		END
	
	IF @OldOpId<>@Id AND EXISTS (SELECT * FROM UserOp WHERE Id=@Id)
		BEGIN
			SELECT @ErrDesc='同标识操作已经存在';
			RETURN -4;	
		END
	
	UPDATE UserOp SET Id=@Id,Name=@Name,Intro=@Intro WHERE Id=@OldOpId;
	RETURN  @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[RVUpdateUserPwd]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[RVUpdateUserPwd]
	@UserId INT,
	@OldPassword VARCHAR(32),
	@Password VARCHAR(32),
	@ErrDesc VARCHAR(128) OUT
AS
BEGIN 
	SET NOCOUNT ON; 

	IF LEN(@Password) < 6
		BEGIN
			SELECT @ErrDesc='密码长度必须大于 5';
			RETURN -1			
		END
	
	IF NOT EXISTS (SELECT * FROM UserInfo WHERE Id=@UserId AND Pwd=@OldPassword)
		BEGIN
			SELECT @ErrDesc='用户名密码检验失败'
			RETURN -2
		END
	  
	UPDATE UserInfo SET Pwd=@Password WHERE Id=@UserId
	RETURN @@ROWCOUNT
END

GO
/****** Object:  StoredProcedure [dbo].[VRGetUserGroup]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[VRGetUserGroup]
	@UserId INT,
	@GroupId INT OUT,
	@GroupName VARCHAR(32) OUT,
	@GroupIntro VARCHAR(256) OUT
AS
BEGIN 
	SET NOCOUNT ON; 
	SELECT @GroupId=GroupId FROM UserInfo WHERE Id=@UserId
	IF @GroupId IS NOT NULL
		SELECT @GroupName=Name, @GroupIntro=Intro FROM UserGroup WHERE Id=@GroupId
END

GO
/****** Object:  Table [dbo].[Log]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Log](
	[Id] [bigint] IDENTITY(1,1) NOT NULL,
	[Time] [datetime] NOT NULL,
	[OpId] [int] NOT NULL,
	[Lvl] [tinyint] NOT NULL,
	[Kword] [varchar](50) NOT NULL,
	[Txt] [varchar](1024) NOT NULL,
 CONSTRAINT [PK_Log] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserGroup]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserGroup](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](32) NOT NULL,
	[Parent] [int] NOT NULL,
	[Intro] [varchar](256) NULL,
 CONSTRAINT [PK_Grade_1] PRIMARY KEY CLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserGroupOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserGroupOp](
	[GroupId] [int] NOT NULL,
	[OpId] [int] NOT NULL,
 CONSTRAINT [PK_UserGroupOp] PRIMARY KEY CLUSTERED 
(
	[GroupId] ASC,
	[OpId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[UserInfo]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserInfo](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](32) NOT NULL,
	[Pwd] [varchar](32) NOT NULL,
	[GroupId] [int] NOT NULL,
	[CreateTime] [datetime] NOT NULL,
 CONSTRAINT [PK_UserInfo] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserOp]    Script Date: 2013/1/24 11:58:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserOp](
	[Id] [int] NOT NULL,
	[Name] [varchar](32) NOT NULL,
	[Intro] [varchar](256) NULL,
 CONSTRAINT [PK_UserOp] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
ALTER TABLE [dbo].[Log] ADD  CONSTRAINT [DF_Log_Time]  DEFAULT (getdate()) FOR [Time]
GO
ALTER TABLE [dbo].[Log] ADD  CONSTRAINT [DF_Log_OpId]  DEFAULT ((0)) FOR [OpId]
GO
ALTER TABLE [dbo].[Log] ADD  CONSTRAINT [DF_Log_Lvl]  DEFAULT ((0)) FOR [Lvl]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_CreateTime]  DEFAULT (getdate()) FOR [CreateTime]
GO
USE [master]
GO
ALTER DATABASE [Prop] SET  READ_WRITE 
GO
