<?php /* Smarty version 2.6.22, created on 2011-07-16 13:00:39
         compiled from login.html */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>后台管理登陆</title>
<?php echo '
<style>
.body {background: #FFF;font-family: "微软雅黑";font-weight:bold;color:#000;font-size:14px;}
#login{border: 1px solid #000;background:#FFF;margin:150px auto; width:400px;}
.pass{background: #FFF;}
</style>
'; ?>

</head>

<body class="body">
<center>
<div id="login">
<form action="admin.php?act=login" method="post">
<br />
<p align="center">后台管理员登陆</p>
<table width=100%  cellspacing=0 cellpadding=3 class="pass">
<tr>
	<td valign=middle width=40% align=right>用户名：</td>
	<td valign=middle><input name="username" type="text" style="width:140px;height:18px;" /></td>
</tr>
<tr>
	<td valign=middle align=right>密码：</td>
	<td valign=middle><input name="password" type="password" style="width:140px;height:18px;" /></td>
</tr>
</table>
<input name="safe_url" type="hidden" value="<?php echo $this->_tpl_vars['safe_url']; ?>
" />
<p align="center"><input name="" type="submit" value="登陆"  /></p>
</form>
<br />

</div>
</center>
</body>
</html>