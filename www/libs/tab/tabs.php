<?
class tabs {
	var $name;
	var $tabs;
	var $active;
	var $current;
	var $title;
	var $alternativeStyle;


    function __construct($name, $title = '', $alternativeStyle = false){
        $this->name = $name;
		$this->title = $title;
		$this->alternativeStyle = $alternativeStyle;
    }

	function start($name){
		if(!$this->alternativeStyle) {
			if (empty($this->active)){ $this->active = $name; }
		}
		$this->current = $name;
		ob_start();
	}

	function end(){
		$this->tabs[$this->current] = ob_get_contents();
		ob_end_clean();
	}

	function run(){
		if (count($this->tabs) > 0){
			echo "<DIV CLASS='tabs'>\n";
			$jsClear = "";
			foreach($this->tabs as $tabname => $tabcontent){
				$tabid = "tab_".$this->name."_$tabname";
				$contentid = "tabcontent_".$this->name."_$tabname";
				$jsClear .= "\tdocument.getElementById('$tabid').className = 'tab_inactive".(($this->alternativeStyle)?"_alt'":"'").";\n";
				$jsClear .= "\tdocument.getElementById('$contentid').style.display = 'none';\n";
			}
			echo "<script type=\"text/javascript\">\n";
			echo "function tab_".$this->name."(id){\n";
			echo "$jsClear";
			echo "\tdocument.getElementById('tab_".$this->name."_'+id).className = 'tab_active".(($this->alternativeStyle)?"_alt'":"'").";\n";
			echo "\tdocument.getElementById('tabcontent_".$this->name."_'+id).style.display = '';\n";
			echo "}\n";
			echo "</script>\n";
			if(!empty($this->title)) {
                echo "<DIV STYLE='clear:both;'><h1>".$this->title."</h1></DIV>\n";
            }
			foreach($this->tabs as $tabname => $tabcontent){
				$tabid = "tab_".$this->name."_$tabname";
				$contentid = "tabcontent_".$this->name."_$tabname";
				echo "<DIV CLASS='";
				if ($this->active == $tabname){ echo "tab_active".(($this->alternativeStyle)?"_alt":""); }else{ echo "tab_inactive".(($this->alternativeStyle)?"_alt":""); }
				echo "' ID='$tabid' ";
				echo "onClick=\"tab_".$this->name."('$tabname');\">$tabname</DIV>\n";
			}
			echo "<DIV STYLE='clear:both;'></DIV>\n";
			foreach($this->tabs as $tabname => $tabcontent){
				$contentid = "tabcontent_".$this->name."_$tabname";
				echo "<DIV ID = '$contentid' CLASS='tab_content".(($this->alternativeStyle)?"_alt'":"'")." STYLE='display: ";
				if ($this->active == $tabname){ echo "block"; }else{ echo "none"; }
				echo ";'>$tabcontent</DIV>\n";
			}
			echo "</DIV>\n";
			echo "<DIV STYLE='clear: both;'></DIV>\n";
		}
	}
}
?>