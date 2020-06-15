function add2onchange(elem_name,jscode)
{
	if (elem_name&&jscode)
	{
		if (getElement(elem_name).onchange)
		{
			eval("getElement('"+elem_name+"').onchange=function () {"+getElement(elem_name).onchange.toString().replace(/^[^{]*{(.*)/,jscode+"$1"));
		}
		else
		{
			eval("getElement('"+elem_name+"').onchange=function() {"+jscode+"}");
		}
	}
}

function add2onblur(elem_name,jscode)
{
	if (elem_name&&jscode)
	{
		if (getElement(elem_name).onblur)
		{
			eval("getElement('"+elem_name+"').onblur=function () {"+getElement(elem_name).onblur.toString().replace(/^[^{]*{(.*)/,jscode+"$1"));
		}
		else
		{
			eval("getElement('"+elem_name+"').onblur=function() {"+jscode+"}");
		}
	}
}


function add2onload(jscode)
{
	if (jscode)
	{
		if (document.body.onload)
		{
			eval("document.body.onload=function () {"+document.body.onload.toString().replace(/^[^{]*{(.*)/,jscode+"$1"));
		}
		else
		{
			eval("document.body.onload=function() {"+jscode+"}");
		}
	}
}


function getElement(id, alwaysObject)
{
	var elem;
	try
	{
		if (document.all)
			elem = document.all[id];
		else
			elem = document.getElementById(id);

		
		if (!elem)
		{
			elem = document.getElementByName(id);
		}

		if (!elem && alwaysObject) elem = {};

		return elem;
	}
	catch (e)
	{
		return null;
	}
}

function optionValue(name)
{
	try
	{
		return getElement(name).options[getElement(name).selectedIndex].value;
	}
	catch (e)
	{
		return null;
	}
}

function selectLength(name)
{
	try
	{
		return getElement(name).options.length;
	}
	catch (e)
	{
		return null;
	}
}


function optionText(name)
{
	try
	{
		return getElement(name).options[getElement(name).selectedIndex].text;
	}
	catch (e)
	{
		return null;
	}
}

function selectOption(select, value)
{
	if (!value)
		value="";
	else
		value=value.toString();
	try
	{
		for (var i=0; i<select.options.length; i++)
		{
			if (select.options[i].value.toString()==value)
			{
				select.selectedIndex=i;
				return true;
			}
		}
	}
	catch (e) {}
	return false;
}


function latvianDate(datestr)
{
	var datepattern=new RegExp('^([0-9]{2})\.([0-9]{2})\.([0-9]{4})$');
	if ((datestr)&&(t = datestr.match(datepattern)))
	{
		var n_year=parseInt(t[3]);
		var n_month=parseInt(t[2])-1;
		var n_date=parseInt(t[1]);
		if ((n_month<=11)&&(n_month>=0))
		{
			var event_date=new Date(n_year,n_month,n_date);
			if ((event_date.getYear()==n_year)&&(event_date.getMonth()==n_month)&&(event_date.getDate()==n_date))
			{
				return event_date;
			}
		}
	}
	return false;
}

function strDate(datestr)
{
	if (!isDate(datestr)) return false;
	var datepattern=new RegExp('^([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{4})$');
	if (datestr)
	{
		if (t = datestr.match(datepattern))
		{
			var n_year=t[3];
			var n_month=t[2];
			var n_date=t[1];
			var dateint=parseInt((n_year*10000)+((n_month)*100)+(n_date*1));
			return dateint;
		}
	}
	return false;
}

function currentDateInt()
{
	var event_date=new Date();
	if (event_date.getDate())
	{
		return parseInt((event_date.getYear()*10000)+((event_date.getMonth()+1)*100)+event_date.getDate());
	}
	else return -1;
}


///////////////////////////////////////////////////////////////////////////////////



function isInteger(s)
{
	var i;
	for (i = 0; i < s.length; i++)
	{   
		// Check that current character is integer.
	        var c = s.charAt(i);
	        if (((c < "0") || (c > "9"))) return false;
	}
	return true;
}

function stripCharsInBag(s, bag)
{
	var i;
	var returnString = "";
	// Search through string's characters one by one.
	// If character is not in bag, append to returnString.
	for (i = 0; i < s.length; i++){   
		var c = s.charAt(i);
		if (bag.indexOf(c) == -1) returnString += c;
	}
	return returnString;
}


function daysInFebruary (year)
{
	// February has 29 days in any year evenly divisible by four,
	// EXCEPT for centurial years which are not also divisible by 400.
	return (((year % 4 == 0) && ( (!(year % 100 == 0)) || (year % 400 == 0))) ? 29 : 28 );
}

function DaysArray(n) 
{
	for (var i = 1; i <= n; i++) {
		this[i] = 31
		if (i==4 || i==6 || i==9 || i==11) {this[i] = 30}
		if (i==2) {this[i] = 29}
	} 
	return this
}

function isDate(dtStr){
		
	// ja datums ir tuks
	if (dtStr.length==0)
	{
		return true;
	}

	var daysInMonth = DaysArray(12)
	var pos1=dtStr.indexOf('.')
	var pos2=dtStr.indexOf('.',pos1+1)
	var strDay=dtStr.substring(0,pos1)
	var strMonth=dtStr.substring(pos1+1,pos2)
	var strYear=dtStr.substring(pos2+1)
	strYr=strYear
	if (strDay.charAt(0)=="0" && strDay.length>1) strDay=strDay.substring(1)
	if (strMonth.charAt(0)=="0" && strMonth.length>1) strMonth=strMonth.substring(1)
	for (var i = 1; i <= 3; i++) {
	 	if (strYr.charAt(0)=="0" && strYr.length>1) 
		strYr=strYr.substring(1)
	}
	month=parseInt(strMonth)
	day=parseInt(strDay)
	year=parseInt(strYr)
	if (pos1==-1 || pos2==-1)
	{
		return false
	}
	if (strMonth.length<1 || month<1 || month>12)
	{
		return false
	}
	if (strDay.length<1 || day<1 || day>31 || (month==2 && day>daysInFebruary(year)) || day > daysInMonth[month])
	{
		return false
	}
	if (strYear.length != 4 || year==0 )
	{
		return false
	}
	if (dtStr.indexOf('.',pos2+1)!=-1 || isInteger(stripCharsInBag(dtStr, '.'))==false){
		
		return false
	}
	
	return true
}


function isTime(dtStr)
{

	if (dtStr.length==0)
	{
		return true;
	}

	if (dtStr.length>5)
	{
		return false;
	}

	var pos1=dtStr.indexOf(':')
	var strHour=dtStr.substring(0,pos1)
	var strMin=dtStr.substring(pos1+1)
	hour=parseInt(strHour)
	min=parseInt(strMin)
	if (pos1==-1)
	{
		return false
	}
	if (strHour.length<1 || strHour.length>2 || hour<0 || hour>23)
	{
		return false
	}
	if (strMin.length<1 || strMin.length>2 || min<0 || min>59)
	{
		return false
	}

	if (!isInteger(stripCharsInBag(dtStr, ':')))
	{
		return false
	}

	return true
}


function isDateTime(dtStr)
{
	if (dtStr.length==0)
	{
		return true;
	}

	if (dtStr.length>16)
	{
		return false;
	}

	var pos1=dtStr.indexOf(' ')
	var date=dtStr.substring(0,pos1)
	var time=dtStr.substring(pos1+1)
	if ( (pos1==-1) || (!isTime(time)) || (!isDate(date)) )
	{
		return false
	}
	return true
}

function textDateToTimeStamp(dtStr)
{
	var pos1=dtStr.indexOf('.')
	var pos2=dtStr.indexOf('.',pos1+1)
	var strDay=dtStr.substring(0,pos1)
	var strMonth=dtStr.substring(pos1+1,pos2)
	var strYear=dtStr.substring(pos2+1)
	var d = new Date();
        d.setMonth(parseInt(strMonth))
	d.setDate(parseInt(strDay))
	d.setYear(parseInt(strYear))
	var timestamp=d.getTime();
	return timestamp;
}

function showError( elementID, errorMessage, formName )
{

	if (isSet(elementID))
	{
		//alert(formName);
		var	el, tb;
		
	    if(formName == '') {
			el = document.getElementsByName( elementID );
			tb = el[ 0 ].parentNode;
		} else {
			el = document.forms[formName][elementID];
			tb = el.parentNode;
		}
		//alert(tb);
	    
		var span = document.createElement( 'DIV' );
		span.style.cssText = 'color: red';
		errSpans[ errSpans.length ] = span;
		span.appendChild( document.createTextNode( errorMessage ) );
		tb.insertBefore(span, tb.childNodes[ 0 ]);
		//tb.className = 'error';
	}
}

function removeErrSpans()
{
	for( i = 0; i < errSpans.length; i++ )
	{
		//errSpans[ i ].parentNode.className = 'standart_row';
		errSpans[ i ].parentNode.removeChild( errSpans[ i ] );
	}
	errSpans = new Array();
}

function isInt(strString)
{
	if (strString.length == 0) return true;

	var strValidChars = "0123456789-";
	var strChar;

	//  test strString consists of valid characters listed above
	for (i = 0; i < strString.length ; i++)
	{
		strChar = strString.charAt(i);
		if (strValidChars.indexOf(strChar) == -1)
		{
			return false;
		}
	}
	return true;

}

function isDouble(strString, fractionAmount)
{

	if (strString.length == 0) return true;

	var whole='';
	var fraction='';

	var pos=strString.indexOf('.')
	if (pos==-1)
	{
		whole=strString;
	}
	else
	{
		whole=strString.substring(0,pos);
		fraction=strString.substring(pos+1);
	}

	if (isInt(whole) && isInt(fraction) && fraction.length<=fractionAmount)
	{
		return true;
	}

	return false;
} 

function isNumeric(strString)
//  check for valid numeric strings	
{
	return isDouble(strString, 0);
}

function isAlphanumeric(alphane)
{
	var numaric = alphane;
	for(var j=0; j<numaric.length; j++)
	{
	  var alphaa = numaric.charAt(j);
	  var hh = alphaa.charCodeAt(0);

	  if((hh > 47 && hh<58) || (hh > 64 && hh<91) || (hh > 96 && hh<123) || (hh == 95))
	  {
	  }
	  else
      {
      	 return false;
	  }
 	}
    return true;
}
function isToIdn(alphane, st_id, st_tr_id, type)
{
	var x = alphane.toLowerCase();

	if((type == st_id || type == st_tr_id) && x == '---') return true;
  
	if(x.length == 5 && isAlphanumeric(x))
	{
		 if(x.charAt(0) == 'b' || x.charAt(0) == 'c')
		 {
			 return true;
		 }
	}
  return false;
}

function isAlpha(alphane)
{
	var numaric = alphane;
	for(var j=0; j<numaric.length; j++)
	{
	  var alphaa = numaric.charAt(j);
	  var hh = alphaa.charCodeAt(0);

	  if (hh > 64 && hh<91)
	  {
	  }
	  else
      {
      	 return false;
	  }
 	}
    return true;
}

function isAlphanumericOnly(alphane)
{
	var numaric = alphane;
	for(var j=0; j<numaric.length; j++)
	{
	  var alphaa = numaric.charAt(j);
	  var hh = alphaa.charCodeAt(0);

	  if((hh > 47 && hh<58) || (hh > 64 && hh<91) || (hh > 96 && hh<123))
	  {
	  }
	  else
      {
      	 return false;
	  }
 	}
    return true;
}

function isKvikStep(  strString, strCompare)
{
    var resultStr = '';

    if (isInt(strString))
    {
         resultStr =  strCompare + '-' +  strString;

    }
    else
    {
	  var parts = strString.split('-');
                    var codes = strCompare.split(';');
          // chek format
                 for (var i = 0; i < codes.length; i++)
                 {
         if(  parts[0].toUpperCase() ==  codes[i].toUpperCase())
         {
	     var pattern = new RegExp('^([a-z]){1,8}-[0-9]{1,7}$', 'i');
           
           if (pattern.test(strString))
           {
             return strString.toUpperCase();
           }
           else
           {
             return 'FALSE';
           }
         }         
              }
              return 'FALSE';
    }
    return resultStr.toUpperCase();
}

function convertStrToNum(strString)
{
	if (isInt(strString))
	{
		var r=0;
		var d=1;
		var sign=1;
		for (i = strString.length-1; i > -1 ; i--)
		{
			num=strString.substring(i,i+1);
			if (num=='-')
			{
				r=-r;
			}
			else
			{
				r=r+num*d;	
				d=d*10;
			}
		}	
		return r;
	}
	return false;
}

function isUrl(url)
{
    var pattern = /(ftp|http|https):\/\/(\w+:{0,1}\w*@)?(\S+)(:[0-9]+)?(\/|\/([\w#!:.?+=&%@!\-\/]))?/;        if (pattern.test(url))
     {
       return true;
     }
     return false;
}

function isPersCode(value)
{
	var strValidChars = "0123456789#";
        if (value.length == 0 )
        {
        	return true;
        }

	if (value.length != 11) 
	{
		return false;
	}

	for (i = 0; i < value.length; i++)
	{
		strChar = value.charAt(i);
		/*
		if (i==6)
		{
			if (strChar != '-')
			{
				return false;
			}
		}
		else
		*/

		{
			if (strValidChars.indexOf(strChar) == -1)
			{
				return false;
			}
		}
	}
	return true;
}


function checkPersCode(fieldName,showError)
{
	var value = document.all[fieldName].value;
	var kluduZinojums = "Personas kods nav pareizs.";
	var b=true;

	b=isPersCode(value);

	if (b==false)
	{
		document.all[fieldName].focus();
		if (showError)
		{
			window.alert(kluduZinojums);
		}
	}
	return b;
}

function isDelete()
{

	if (confirm('Vai Jūs tiešām vēlaties dzēst šo ierakstu?'))
	{
		return true;
	}
	else
	{
		return false;
	}

//	return showWarning('Vai J?s tie??m v?laties dz?st ?o ierakstu?',url);
}

function isDeleteWithMessage(text)
{

	if (confirm(text))
	{
		return true;
	}
	else
	{
		return false;
	}

//	return showWarning('Vai J?s tie??m v?laties dz?st ?o ierakstu?',url);
}

function isExit(url)
{
	if (confirm('Vai Jūs tiešām vēlaties dzēst šo ierakstu?') == true)
	{ 
		window.location=url;
	}
	return false;
}

function trim(s)
{ 
	while (s.substring(0,1) == ' ') 
		{ s = s.substring(1,s.length); } 
	while (s.substring(s.length-1,s.length) == ' ') 
		{ s = s.substring(0,s.length-1); } 
	return s; 
} 

function strlen(s) 
{ 
	return s.length;
} 

function moveCursor(name, isMove)
{
	if (isMove)
	{
		if (isShow(name))
		{
			document.all[name].focus();
			return false;
		}
		return true;
	}
	return false;
}

function moveCursorInForm(formname, name, isMove)
{
	if (isMove)
	{
		if (isShowFormField(formname,name))
		{
			document.forms[formname][name].focus();
			return false;
		}
		return true;
	}
	return false;
}



function isEmptyField(name)
{
	if (isSet(name))
	{
		switch (document.all[name].type)
		{
			case 'checkbox':
				if (document.all[name].checked) 
				{
					return false;
				}
				break;
			default:
				if (document.all[name].value!='')
				{
					return false;
				}
				break;
		}
	}
	return true;
}

function isEmptyFormField(formname,name)
{
	if (isSetFormField(formname,name))
	{
		switch (document.forms[formname][name].type)
		{
			case 'checkbox':
				if (document.forms[formname][name].checked) 
				{
					return false;
				}
				break;
			default:
				if (document.forms[formname][name].value!='') 
				{
					return false;
				}
				break;
		}
	}

	if (isSetFormField(formname,name+'[]'))
	{
		switch (document.forms[formname][name+'[]'].type)
		{
			default:
				if (document.forms[formname][name+'[]'].value!='') 
				{
					return false;
				}
				break;
		}
	}
	return true;
}


function setKlsValue(name,value)
{
	if (value!=classif.node(name).value)
	{
		classif.node(name).value=value;
		classif.fetch(name);
		classif.change(name);
	}
	disableField(name,false);
}

function isSetFormField(formname,name)
{
	if (typeof document.forms[formname][name] == "undefined")
	{
		return false;
	}
	return true;
}

function isSet(name)
{
	if (typeof document.all[name] == "undefined") 
	{
		return false;
	}
	return true;
}

function disableField(name,value)
{
	if (isSet(name)) 
	{
		document.all[name].disabled=value;
	}
}

function disableFormField(formname,name,value)
{
	if (isSetFormField(formname,name)) 
	{
		document.forms[formname][name].disabled=value;
	}
}

function setValue(name,value)
{   
    if (isSet(name))
	{

       	switch (document.all[name].type)
		{
			case "checkbox":
				if (value==1)
				{
					document.all[name].checked=true;
				}
				else
				{
					document.all[name].checked=false;
				}
				break;
			case "select-one":
			default:
				document.all[name].value=value;
		}
	   	//document.all[name].fireEvent("onchange");
        //alert(document.all[name].value) ;
	}
}



function setFormValue(formname, name,value)
{
	if (isSetFormField(formname,name))
	{  //alert(typeof document.forms[formname][name]);
        switch (document.all[name].type)
		{
			case "checkbox":
				if (value==1)
				{
					document.forms[formname][name].checked=true;
				}
				else
				{
					document.forms[formname][name].checked=false;
				}
				break;
			case "select-one":
             
			default:
			   	document.forms[formname][name].value=value;
		}
	   	//document.forms[formname][name].fireEvent("onchange");
 	}

}




function getLabelFieldInForm(formname,name,value)
{
        if (isSetFormField(formname,name))
        {
		switch (document.forms[formname][name].type)
		{
			case "select-one": 
				if (value=='') return '';
				for (i=0;i<document.forms[formname][name].length;i++)
				{
					if ( document.forms[formname][name].options[ i ].value == value)
					{
						return document.forms[formname][name].options[ i ].text;
					}
				}
				return '';
				break;
			case "checkbox":
				if (document.forms[formname][name].checked)
				{
					return 1;
				}
				else
				{
					return 0;
				}
				break;
			default: 
				return value;
		 }
	}
	else
	{
		return value;
	}
}

function copyValue(name1,name2)
{
	switch (document.all[name1].type)
	{
		case "checkbox": 
			if (document.all[name1].checked)
			{
				document.all[name2].value=1;
			}
			else
			{
				document.all[name2].value='';
			}
			break;
		default: 
			document.all[name2].value=document.all[name1].value;

	 }
	document.all[name2].fireEvent("onchange");

}

function getValue(name)
{
        if (isSet(name))
        {
		switch (document.all[name].type)
		{
			case "checkbox":
				if (document.all[name].checked)
				{
					return 1;
				}
				else
				{
					return '';
				}
				break;
			case "select-one":
			default:
				return document.all[name].value;
				break;
		 }
	}
}

function getFormValue(formname, name)
{
        if (isSet(name))
        {
		switch (document.forms[formname][name].type)
		{
			case "checkbox":
				if (document.forms[formname][name].checked)
				{
					return 1;
				}
				else
				{
					return '';
				}
				break;
			case "select-one":
			default:
				return document.forms[formname][name].value;
				break;
		 }
	}
    return false;
}

function createXHR() 
{
    var request = false;
        try {
            request = new ActiveXObject('Msxml2.XMLHTTP');
        }
        catch (err2) {
            try {
                request = new ActiveXObject('Microsoft.XMLHTTP');
            }
            catch (err3) {
		try {
			request = new XMLHttpRequest();
		}
		catch (err1) 
		{
			request = false;
		}
            }
        }
    return request;
}
function xmlHttpGetValue(szURL)
{ 
 var xhr=createXHR();
 xhr.open("POST", szURL, false);
 xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
 
 reqText = 'xmlHttp=true';
 //getElement("zone").innerHTML="Started...";
 var res = "";
 xhr.onreadystatechange=function()
 { 
	//getElement("zone").innerHTML="Wait server...";
	//alert(xhr.readyState);
	if(xhr.readyState == 4)
	{
	  //  alert("I am here xmlhttp.onreadystatechange"); 
        //getElement("zone").innerHTML= xhr.responseText;
        if(xhr.status==200)
        { 
            //alert(xhr.status); 
            //alert(xhr.responseText);
  
	        //getElement("zone").innerHTML= xhr.responseText;	
	        //alert(xhr.responseText);
	        res = xhr.responseText;
res = res.replace(/<\/?[a-z][a-z0-9]*[^<>]*>/ig, "");
//res = res.replace("var ___cp_connecta_prefix = 'https://portal.delta.latvenergo.lv';", "");
res = res.replace("var ___cp_connectra_prefix = \'https://portal.delta.latvenergo.lv\';", "");

//alert(res);
	    }
	    else
	    {
	        //alert("Problem retrieving data:" + xhr.status);
	        res = "";
	    } 
        
	} 
 }; 
 xhr.send(reqText); 
 return res;
} 
/*
function xmlHttpGetValue1(szURL)
{
	var objHTTP = new ActiveXObject("Microsoft.XMLHTTP");
	var szHttpMethod = "POST";
	objHTTP.Open(szHttpMethod, szURL, false);
	objHTTP.SetRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	reqText = 'xmlHttp=true';
	objHTTP.Send(reqText);
	var szReply = objHTTP.ResponseText;

	if (objHTTP.status != 200)
	{
		szReply = "";
	}
	return szReply;
}
*/
// PHP-compatible urlencode() for Javascript
function urlencode(s) {
  s = encodeURIComponent(s);
  return s.replace(/~/g,'%7E').replace(/%20/g,'+');
}

function enableAll(frmName)
{
	m=document.forms[frmName];
	for (f in m)
	{
		if (isSet(f))
		{
			document.all[f].disabled=false;
		}
	}
}

function isEnterPress(event)
{
	if (event.keyCode==13) 
	{
		return true;
	}
	return false;
}

function isShow(name)
{
	//if (isSet(name)) 
	{
		if (document.all[name].style.display!='none' && document.all[name].style.visibility!='hidden' && document.all[name].disabled!=true)
		{
			return true;
		}
	}
	return false;
}

function isShowFormField(formname,name)
{
	//if (isSet(name)) 
	{
		if (document.forms[formname][name].style.display=='none' || document.forms[formname][name].style.visibility=='hidden' || document.forms[formname][name].disabled==true)
		{
			return false;
		}
	}
	return true;
}


function disableCitsFieldDependingOnClassificatorValue(name1,name2,value)
{
        if (getElement(name1).value === value)
                getElement(name2).disabled = false;
        else
        {
                getElement(name2).value = '';
                getElement(name2).disabled = true;
        }
}


function dateConvert(format,dtStr)
{
	var pos1=dtStr.indexOf('.')
	var pos2=dtStr.indexOf('.',pos1+1)
	var strDay=dtStr.substring(0,pos1)
	var strMonth=dtStr.substring(pos1+1,pos2)
	var strYear=dtStr.substring(pos2+1)
	if (strDay.length<2) strDay='0'+strDay;
	if (strMonth.length<2) strMonth='0'+strMonth;
	format=format.replace("Y",strYear);
	format=format.replace("M",strMonth);
	format=format.replace("D",strDay);
	return format;
}

function showWarning(message,url)
{
	if (confirm(message) == true) 
	{ 
		window.location=url;
	}
	return false;
}

function linkGlbSearch(subsysId)
{
	if (isSet('glbMklIsRez'))
	{
		var persId=0;
		if (isSetFormField('glbMklFrmRez','persId'))
		{

			// if count of result is _1_, IE don't make array :(( 
			if (typeof document.forms['glbMklFrmRez']['persId'].length == "undefined")
			{
				if (document.forms['glbMklFrmRez']['persId'].checked)
				{
					persId=document.forms['glbMklFrmRez']['persId'].value;
				}
			}
			else
			{
				for (i=0;i<document.forms['glbMklFrmRez']['persId'].length;i++)
		        	{
					if (document.forms['glbMklFrmRez']['persId'][i].checked)
					{
						persId=document.forms['glbMklFrmRez']['persId'][i].value;
					}
				}
			}
		}

		if (persId==0)
		{
			return true;
		}
		else
		{
			if (isSetFormField('glbMklFrmRez',subsysId+''+persId))
			{
				window.location=document.forms['glbMklFrmRez'][subsysId+''+persId].value;
			}	
			else
			{
				if (isSetFormField('glbMklFrmRez','newWindow'+subsysId+''+persId))
				{
					window.open(document.forms['glbMklFrmRez']['newWindow'+subsysId+''+persId].value, '', 'toolbar=no,scrollbars=yes,resizable=yes,width=740,height=530,left=0,right=0')
				}	
			}
			return false;
		}
	}
	else
	{
		return true;
	}
}

function htmlspecialchars(ch) 
{
   ch = ch.replace(/&/g,"&amp;");
   ch = ch.replace(/\"/g,"&quot;");
   ch = ch.replace(/\'/g,"&#039;");
   ch = ch.replace(/</g,"&lt;");
   ch = ch.replace(/>/g,"&gt;");
   return ch;
}

// function explode(inputstring, separators, includeEmpties) for exploding inputstring by separator
// inputstring - string for exploding
// separator - simbol by whitch inputsting will bi exploding
// includeEmpties <0|false|'', white spaces will be egnored
function explode(inputstring, separators, includeEmpties) 
{
	inputstring = new String(inputstring);
	separators = new String(separators);

	if(separators == "undefined") 
	{
		separators = " :;";
	}

	fixedExplode = new Array(1);
	currentElement = "";
	count = 0;

	for(x=0; x < inputstring.length; x++)
	{
		char = inputstring.charAt(x);
		if(separators.indexOf(char) != -1) 
		{
			if ( ( (includeEmpties <= 0) || (includeEmpties == false)) && (currentElement == "")) 
			{ }
			else 
			{
				fixedExplode[count] = currentElement;
				count++;
				currentElement = ""; 
			} 
		}
		else 
		{ 
			currentElement += char; 
		}
	}

	if (( ! (includeEmpties <= 0) && (includeEmpties != false)) || (currentElement != "")) 
	{
		fixedExplode[count] = currentElement; 
	}
	return fixedExplode;
}

// function getFormId(frame) - to get ID of form in the frame
// frame - frame number
function getFormId(frame)
{
	var formId = '';
	var frameUrl = eval("parent."+frame+".location.href");
	var urlParts = explode(frameUrl, '&', false);
	for(i=0; i<urlParts.length; i++)
	{
		if(urlParts[i].substring(0,6) == 'formId')
		{
			var formIdPart = explode(urlParts[i], '=', false);
			var formId = formIdPart[1];
		}
	}
	return formId;
}

// function reloadFrame(num, url) for reloading frame content
// num - frame number(1- frame_1; 2 - frame_2; 3 - frameButtons; 23 - frame_2&frameButtons)
// url - of frame content; if url='', put blank page in to the frame
function reloadFrame(num, url)
{
	frameName = '';
	switch(num)
	{
		case 1:
			frameName = 'frame_1';
			break;
		case 2:
			frameName = 'frame_2';
			break;
		case 3:
			frameName = 'frameButtons';
			break;
	}
	
	if(url == '')
	{
		switch(num)
		{
			case 23:
				parent.frame_2.location.replace('./?formId=blank');
				parent.frameButtons.location.replace('./?formId=blank');
				break;
			case 1:
			case 2:
			case 3:
				parent[frameName].location.replace('./?formId=blank');
				break;
		}
	}
	else
	{
		parent[frameName].location.replace(url);
	}
	return true;
}


// for making active table row
var old=false;
function makeActiveRow(o,url)
{
	if (old)
	{
		old.className="table_cell_3"
	}
	o.className="table_cell_4";
	reloadFrame(2,url);
	old=o;
}

function unActiveRow()
{
	if (old)
	{
		old.className="table_cell_3"
		old=false;
	}
}

var old2=false;
var data_id2=false;
function makeActiveRow2(o,id)
{
	if (old2)
	{
		old2.className="clickable"
	}
	o.className="clickable active";
	data_id2=id;
	old2=o;
}

// function refreshFrame(num) for refreashing frame content
// num - frame number(1- frame_1; 2 - frame_2; 3 - frameButtons)
function refreshFrame(num)
{
	frameName = '';
	switch(num)
	{
		case 1:
			frameName = 'frame_1';
			break;
		case 2:
			frameName = 'frame_2';
			break;
		case 3:
			frameName = 'frameButtons';
			break;
	}
	parent[frameName].location.replace(parent[frameName].location);
	return true;
}

// function refreshFrame(num) for refreashing frame content
// num - frame number(1- frame_1; 2 - frame_2; 3 - frameButtons)
// param will be added to the redirect link
function refreshFramePlusParam(num, paramName, paramValue)
{
	frameName = '';
	switch(num)
	{
		case 1:
			frameName = 'frame_1';
			break;
		case 2:
			frameName = 'frame_2';
			break;
		case 3:
			frameName = 'frameButtons';
			break;
	}
	parent[frameName].location.replace(parent[frameName].location+'&'+paramName+'='+paramValue);
	return true;
}


var newwindow = ''
function openWin(url, param) {
	if (newwindow.location && !newwindow.closed) {
		newwindow.location.href = url; 
		newwindow.focus(); } 
	else
	{ 
	   newwindow=window.open(url,'',param);
	} 
}

function openOriginalWin(url, param)
{
	d=new Date();
	window.open(url,d.getDate()+d.getMonth()+d.getFullYear()+d.getHours()+d.getMinutes()+d.getSeconds()+d.getMilliseconds(),param);
}


function openNewBlock(fieldName)
{

	var i = getRowAmount(fieldName)-1;

	while ( document.all[fieldName+''+i].style.display!='none' )
	{
		i--;
		if (typeof document.all[fieldName+''+i]=='undefined') return false;
	}
if(navigator.appName.indexOf("Internet Explorer")!=-1)
{
	document.all[fieldName+''+i].style.display='block';
}
else
{
       document.all[fieldName+''+i].style = '';
}
	
}

function getRowAmount(fieldName)
{
	var i=0;
	while ( typeof document.all[fieldName+''+(i)]!='undefined' )
	{
	    i++;
	}
	return i;
}

prefereValue = false;
function deleteBlock(node,fieldName,inputFields)
{
    
	var tr = node.parentNode.parentNode;
	var currentRow = (tr.id.replace(fieldName,''))*1;

	var i=currentRow;
	delRowNum = 1;

	while ( typeof document.all[fieldName+''+(i-1)]!='undefined' && document.all[fieldName+''+(i-1)].style.display!='none' )
	{
		for (var j=0;j<inputFields.length;j++)
		{
			var f=inputFields[j];


				document.all[f+''+i].value=document.all[f+''+(i-1)].value;
				document.all[f+''+i].disabled=document.all[f+''+(i-1)].disabled;
				document.all[f+''+i].checked=document.all[f+''+(i-1)].checked;
				document.all[f+''+i].fireEvent('onchange');

		}
		i--;
	}


	for (var j=0;j<inputFields.length;j++)
	{

		var f=inputFields[j];

			document.all[f+''+i].value=(prefereValue)?document.all[f+''+(i-1)].value:'';
			document.all[f+''+i].disabled=false;
			document.all[f+''+i].fireEvent('onchange');

	}
	document.all[fieldName+''+i].style.display='none';
}

function setPosition(divName, posTop, posLeft) {

  var loading = document.getElementById(divName);
  var IpopTop = ((posTop == 0)?(screen.Height - loading.offsetHeight)/2 : posTop);
  var IpopLeft = ((posLeft == 0)?(screen.Width - loading.offsetWidth)/2 : posLeft);

  loading.style.display = "block" ;
  loading.style.position = "absolute";
  loading.style.left = (IpopLeft - loading.offsetWidth/2) + "px";
  loading.style.top = IpopTop + "px";

}

function setPosition1(divName) {

  var loading = document.getElementById(divName);

  var IpopLeft = (screen.Width - loading.offsetWidth)/2 ;

  loading.style.display = "inline" ;

  //loading.style.left = (IpopLeft - loading.offsetWidth) + "px";

}

