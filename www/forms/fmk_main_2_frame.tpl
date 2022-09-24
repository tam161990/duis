<script>

var is_min=0;
var frame_1_size=0;
var frame_2_size=0;
var canResize=true;

function save_size()
{
    frame_1_size="50%";
	frame_2_size="50%";
}

function normal()
{
	if (is_min==1 && canResize)
	{
		var fs = document.getElementById('frameset1');
		fs.rows = frame_1_size+','+frame_2_size;
        
		is_min=0;
	}
}

function min(n)
{
	if (is_min==0)
	{
		save_size();
		is_min=1;
	}
	var fs = document.getElementById('frameset1');
	if (fs) 
	{
		switch(n) 
		{
			case 1:
				fs.rows = '100%,1';
				break;
			case 2:
				if (canResize)
				{
					fs.rows = '1,100%';
				}
				break;		}  
	}
}

function disableResize()
{
	var fs = document.getElementById('frame_1');
	fs.noResize=true;
	canResize=false;
}

function enableResize()
{
	var fs = document.getElementById('frame_1');
	fs.noResize=false;
	canResize=true;
}





</script>


<frameset id="frameset1" rows="50%, 50%" border="0">
	
	<frame src="<?=$frame1Url;?>" frameborder="0" marginheight="0" marginwidth="0" class="frame_border_1" id="frame_1" name="frame_1">
	<frame src="<?=$frame2Url;?>" frameborder="0" marginheight="0" marginwidth="0" class="frame_border_2" name="frame_2" id="frame_2">

</frameset>

