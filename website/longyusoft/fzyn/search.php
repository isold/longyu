<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');



$type=$_GET['type'];


	$resource_category=file_get_contents($domain.'resource_category.php');
	$smarty->assign('resource_category', $resource_category);
	
	$last_resource=file_get_contents($domain.'last_resource.php');
	$smarty->assign('last_resource', $last_resource);
	
	
	$cache_id = md5("resource_category");
$sql = "select id,name,resource_count from ".table('resource_category')." ORDER BY list_order ASC";
$resource_category_list=$db->getall($sql);
$smarty->assign('resource_category_list',$resource_category_list);


$sql='SELECT count(*) FROM '. table('resource');
$resource_count=intval($db->getone($sql));
$smarty->assign('resource_count',$resource_count);

if($type == 'search')
{
	$content=$_POST['search_txt'];
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$cat_id=isset($_GET['cat'])?intval($_GET['cat']):0;

	$page_size=20;
	
	$sql='SELECT count(*) FROM '. table('resource')." WHERE name LIKE '%".$content."%'";
	
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	
	$page_arr=create_page($page_count,$pg,0);
	
	$page_url='resource.php';
	
	$start=($pg-1)*$page_size;
	
	$cache_id = md5("resource_list".$pg);

		$sql = "select a.id,a.cat_id,a.name AS aname,a.number,a.spec,a.origin,a.material,a.weight,a.price,a.upload_time,a.author,a.path,a.image_path,a.view_time,b.name AS bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id WHERE a.name LIKE '%".$content."%' ORDER BY a.upload_time  DESC LIMIT ".$start.' , '.$page_size;

	$resource_list=$db->getall($sql);
	$smarty->assign('resource_list',$resource_list);
	
	$smarty->assign('page_url',$page_url);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$pre=$pg-1; 
	if($pre <= 0)
	{
		$pre = 1;
	}
	$smarty->assign('pre',$pre);
	$next=$pg+1;
	if($next >= $page_count)
	{
		$next = $page_count;
	}
	$smarty->assign('next',$next);	
	$smarty->assign('cat_id',$cat_id);
	
	$smarty->display('resource.html', $cache_id);

}


 ?>