<?php
    // empty variables
	$var1 = '';
	$var2 = '';
	$page = '';
	$agent = '';
	
// set default timezone
        date_default_timezone_set ("Europe/Berlin");
        
// current date & time
        $cur_date = date("d.m.Y");
        $cur_time = date("H:i");
        
// for security, set an allowed user agent
        $agent = "ESP8266HTTPClient";
        
// get HTTP Request-Variables
        $temp1 = $_REQUEST["temp"];
        $press = $_REQUEST["press"];
        $humi = $_REQUEST["humi"];
        
        $agent = $_SERVER["HTTP_USER_AGENT"];
        
// put content from request(page) into variable
        if(isset($_REQUEST["page"]))
        {
                $page = $_REQUEST["page"];
        }

//        echo $page;
        
        switch ($page) {
            case "edit";
              echo $_REQUEST["temp"]." ".$_REQUEST["press"]." ".$_REQUEST["humi"]." ".$_REQUEST["alti"];
              
            break;

            default:
                echo "nope";
                break;
        }
?>
