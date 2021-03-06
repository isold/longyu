﻿<?php 
  define('IN_PBBLOG', true);
  

  include(dirname(__FILE__) . '/include/core.php');
  
  
  //获取公告内容
  $cache_announcement=md5("index_announcement");
	$sql="select * from ".table('announcement');
	$announcement_list=$db->getall($sql);
	$smarty->assign('announcement_list',$announcement_list);
	
	//获取首页图片地址
  /*$cache_index_pic=md5("index_pic");
	$sql="select * from ".table('index_pic');
	$index_pic_list=$db->getall($sql);
	$smarty->assign('index_pic_list',$index_pic_list);*/
	
	//获取最新用户留言
	$cache_id = md5("last_message");
	
	$sql = "select id,post_time,content from ".table('message')." ORDER BY post_time DESC LIMIT 7";
	$last_message_list=$db->getall($sql);
	$smarty->assign('last_message_list',$last_message_list);
	
	
	//获取最新日志
	$cache_id = md5("last_blog");
	$sql = "select a.id,a.title,a.post_time,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 4 ORDER BY post_time DESC LIMIT 6";
	$last_blog_list=$db->getall($sql);
	$smarty->assign('last_blog_list',$last_blog_list);
	
	//获取热门日志
	$cache_id = md5("hot_blog_list");
	$sql = "select a.id,a.title,a.post_time,a.view_count,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 3 ORDER BY post_time DESC LIMIT 6";
	$hot_blog_list=$db->getall($sql);
	$smarty->assign('hot_blog_list',$hot_blog_list);
	
	//日志分类
	$cache_id = md5("blog_category_list");
	$sql = "select id,name,blog_count from ".table('blog_category')." ORDER BY blog_count DESC LIMIT 8";
	$blog_category_list=$db->getall($sql);
	$smarty->assign('blog_category_list',$blog_category_list);
	
	//获取最新资源
	$cache_id = md5("last_resource_list");
	$sql = "select a.id,a.name as aname, a.upload_time, b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id ORDER BY upload_time DESC LIMIT 6";
	$last_resource_list=$db->getall($sql);
	$smarty->assign('last_resource_list',$last_resource_list);
	
	//获取最新资源
	$cache_id = md5("hot_resource_list");
	$sql = "select a.id,a.name as aname,b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id ORDER BY view_time DESC LIMIT 6";
	$hot_resource_list=$db->getall($sql);
	$smarty->assign('hot_resource_list',$hot_resource_list);
	
	//资源分类
	$cache_id = md5("resource_category_list");
	$sql = "select id,name,resource_count from ".table('resource_category')." ORDER BY list_order ASC LIMIT 6";
	$resource_category_list=$db->getall($sql);
	$smarty->assign('resource_category_list',$resource_category_list);
	
	//友情链接
	$cache_id = md5("friend_link_list");
	//$sql = "select id,name,link_url from ".table('friendlink')." ORDER BY id DESC LIMIT 8";
	$sql = "select id,name,link_url from ".table('friendlink')." WHERE lang='".$lan."'";
	$friend_link_list=$db->getall($sql);
	$smarty->assign('friend_link_list',$friend_link_list);
	
	//最新注册用户
	$cache_id = md5("new_user_list");
	$sql = "select id,name from ".table('user')." ORDER BY reg_time DESC LIMIT 8";
	$new_user_list=$db->getall($sql);
	$smarty->assign('new_user_list',$new_user_list);
	
	//注册用户数
	$cache_user_count=md5("web_site_reg_user_count");
	$sql="select count(*) from ".table('user');
	$reg_user_count=intval(($db->getone($sql)));
	$smarty->assign('reg_user_count',$reg_user_count);
	
	//获取最新资源18个用来图片展示
	$cache_id = md5("last_resource_list");
	$sql = "select * from ".table('resource')." WHERE cat_id = 10 AND lang='".$lan."' ORDER BY upload_time DESC LIMIT 18";
	$last_resource_list_18=$db->getall($sql);
	$smarty->assign('last_resource_list_18',$last_resource_list_18);
	
	//获取最新资源18个用来图片展示
	$cache_id = md5("last_resource_list_10");
	$sql = "select * from ".table('resource')." WHERE cat_id = 11 AND weight != 'offer' AND lang='".$lan."' ORDER BY upload_time DESC LIMIT 5";
	$last_resource_list_10=$db->getall($sql);
	$smarty->assign('last_resource_list_10',$last_resource_list_10);
	
	$cache_id = md5("offer_resource_list_5");
	$sql = "select * from ".table('resource')." WHERE cat_id = 11 AND weight = 'offer' AND lang='".$lan."' ORDER BY upload_time DESC LIMIT 5";
	$offer_resource_list_5=$db->getall($sql);
	$smarty->assign('offer_resource_list_5',$offer_resource_list_5);
	
	$smarty->display('main.html');
	?>