<?php
/*+++
|
| Author :��ع��
| ʹ�÷���
|   $shtml = new Shtml($Url,$FileBag,$FolderName,$fileid)
|   $Url��       ҳ�� URL ��ַ
|   $FileBag��   �ļ��б��   1 Ϊ��ָ���ļ���
|         2 Ϊ��Ĭ���ļ���(ʱ��(������))
|        $FolderRoot html�ļ����·��
|   $FolderName ָ���ļ��е����� $FileBagΪ2ʱ ����дΪ��("");
|   $fileid      ��̬ҳ������(��׺ Ĭ��Ϊ .html)
|
|$fileid=2;
|$shtml = new Shtml("http://www.qq.com",1,"","cc",$fileid);
|
/*++*/
class Shtml
{
    var $message1="Error    1: You write class Shtml is Wrong !   The second parameter is 1 or 2 in   this class!.";
    var $message2="Error    2: The file write    Error.";
    function __construct ($Url,$FileBag,$FolderRoot,$FolderName,$fileid)
    {
        $this->Url   = $Url;
        $this->FileBag   = $FileBag;
        $this->FileRoot = $FolderRoot;
        $this->FileName = $FolderName;
        $this->fileid    = $fileid;
        Shtml::useFolder ();
    }
    /*************��ȡ����*******************/
    public function loadcontent ($Folder)
    {
        ob_start();
        require_once $this->Url;
        Shtml::writehtml ($Folder,ob_get_contents());
        ob_clean();
    }
    /********** ָ���ļ���*****************/
    public function useFolder ()
    {
        if($this->FileBag==1)
        {
            $Folder=$this->FileName;
        }
        else if($this->FileBag==2)
        {
            $Folder=date('Ymd',time());
        }
        else
        {
            exit($this->message1);
        }
        if(!is_dir($this->FileRoot.$Folder)){ mkdir($this->FileRoot.$Folder,0700);}
        Shtml::loadcontent ($Folder);
    }
    /********** ���ɾ�̬ҳ��*****************/
    public function writehtml ($Folder,$cache_value)
    {
        $file   = fopen($this->FileRoot.$Folder.'/'.$this->fileid.'.html','w+');
        fwrite($file,$cache_value);
        fclose($file);
    }
}
?>
  