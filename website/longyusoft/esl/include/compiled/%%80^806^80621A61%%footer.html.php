<?php /* Smarty version 2.6.22, created on 2011-10-31 15:11:09
         compiled from footer.html */ ?>
</div>
<!--end content-->

<div class="push">
</div>
</div>
<!--end wrapper-->
<div id="footer">
    <div id="footer-content">
        <div id="footer-item">
            Copyright 2009-2011 <a href="<?php echo $this->_tpl_vars['web_url']; ?>
" target="_parent"><?php echo $this->_tpl_vars['web_name']; ?>
</a>
            All Rights Reserved
        </div>

       <div id="footer-item">
            <?php echo $this->_tpl_vars['foot_content']; ?>

        </div>
                <div id="footer-item">
        	声明：网站部分内容来自互联网，如果用到了不允许转载的文章和图片，请通知我们进行删除。
        </div>
    </div>
    <!--end footer-content-->
</div>
<!--end footer-->

    
</body> 


<script type="text/JavaScript">
alimama_domain_auth="2395151_11017278";
</script>
	

     <!--  header login logout -->
<script type="text/javascript">

        $(document).ready(function () {

            //select all the a tag with name equal to modal
            $('a[name=modal]').click(function (e) {
                //Cancel the link behavior
                e.preventDefault();

                //Get the A tag
                var id = $(this).attr('href');

                //Get the screen height and width
                var maskHeight = $(document).height();
                var maskWidth = $(window).width();

                //Set heigth and width to mask to fill up the whole screen
                $('#mask').css({ 'width': maskWidth, 'height': maskHeight });

                //transition effect		
                $('#mask').fadeIn(1000);
                $('#mask').fadeTo("slow", 0.8);

                //Get the window height and width
                var winH = $(window).height();
                var winW = $(window).width();

                //Set the popup window to center
                $(id).css('top', winH / 2 - $(id).height() / 2);
                $(id).css('left', winW / 2 - $(id).width() / 2);

                //transition effect
                $(id).fadeIn(2000);

            });

            //if close button is clicked
            $('.window .close').click(function (e) {
                //Cancel the link behavior
                e.preventDefault();

                $('#mask').hide();
                $('.window').hide();
            });

            //if mask is clicked
            $('#mask').click(function () {
                $(this).hide();
                $('.window').hide();
            });

        });

    </script>
    
    
     <!--  首页图片播放 -->
    <!--  initialize the slideshow when the DOM is ready -->
<script type="text/javascript">
$(document).ready(function() {
    $('.slideshow').cycle({
		fx: 'scrollLeft',
		next: '.slideshow',
		startingSlide: 1
	});
});
</script>
    
    
    
    <!--  菜单 -->
        <script type="text/javascript">
        $(document).ready(function () {
            $("#menu-one li").hover(
				function () { $("ul", this).fadeIn("fast"); },
				function () { }
			);
            if (document.all) {
                $("#menu-one li").hoverClass("sfHover");
            }
        });

        $.fn.hoverClass = function (c) {
            return this.each(function () {
                $(this).hover(
					function () { $(this).addClass(c); },
					function () { $(this).removeClass(c); }
				);
            });
        };	  
    </script>
    
    <!--  首页相册 -->
    
<script type="text/javascript">
// execute your scripts when the DOM is ready. this is mostly a good habit
$(document).ready(function() {

	// initialize scrollable
	$(".scrollable").scrollable({circular: true}).autoscroll({ autoplay: true });

});
</script>
    
    
    
    
    <!--  相册 -->
    
<script type="text/javascript">
// What is $(document).ready ? See: http://flowplayer.org/tools/documentation/basics.html#document_ready
$(function() {

	// thumbnail scrollable
	$("#thumbnails").scrollable({size: 3, clickable: false}).find("img").each(function(index) {

		// thumbnail images trigger the overlay
		$(this).overlay({

			effect: 'apple',
			target: '#box',
			mask: { maskId: 'mask' },

			// when box is opened, scroll to correct position (in 0 seconds)
			onLoad: function() {
				$("#images").data("scrollable").seekTo(index, 10);
				
						
			}
		});
	});

	

	// scrollable inside the box.
	$("#images").scrollable();

	
	// enable tooltips for the images
	$("#images img").tooltip({
		position: "bottom center",
		offset: [-75, -30],
		opacity: 0.8,
		effect: 'fade',

		// position tooltips relative to the parent scrollable
		relative: true
	});

	

	// enable reflections
	$("#thumbnails img").reflect({height: 0.5, opacity: 0.6});



});
</script>


  <!--  首页公告 -->

<script type="text/javascript">
//滚动插件
(function($){
$.fn.extend({
        Scroll:function(opt,callback){
                //参数初始化
                if(!opt) var opt={};
                var _this=this.eq(0).find("ul:first");
                var        lineH=_this.find("li:first").height(), //获取行高
                        line=opt.line?parseInt(opt.line,10):parseInt(this.height()/lineH,10), //每次滚动的行数，默认为一屏，即父容器高度
                        speed=opt.speed?parseInt(opt.speed,10):500, //卷动速度，数值越大，速度越慢（毫秒）
                        timer=opt.timer?parseInt(opt.timer,10):3000; //滚动的时间间隔（毫秒）
                if(line==0) line=1;
                var upHeight=0-line*lineH;
                //滚动函数
                scrollUp=function(){
                        _this.animate({
                                marginTop:upHeight
                        },speed,function(){
                                for(i=1;i<=line;i++){
                                        _this.find("li:first").appendTo(_this);
                                }
                                _this.css({marginTop:0});
                        });
                }
                //鼠标事件绑定
                _this.hover(function(){
                        clearInterval(timerID);
                },function(){
                        timerID=setInterval("scrollUp()",timer);
                }).mouseout();
        }       
})
})(jQuery);

$(document).ready(function(){
        $("#announcement_body").Scroll({line:9,speed:1000,timer:3000});
});
</script>

<script language="javascript">
function addfavor(url,title) {

var ua = navigator.userAgent.toLowerCase();
if(ua.indexOf("msie 8")>-1){
external.AddToFavoritesBar(url,title,'野牛非洲艺术馆');//IE8
}else{
try {
window.external.addFavorite(url, title);
} catch(e) {
try {
window.sidebar.addPanel(title, url, "");//firefox
} catch(e) {
alert("加入收藏失败，请使用Ctrl+D进行添加");
}
}

}
return false;
}
</script>




</html>