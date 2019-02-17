<?php
    
//  $output = shell_exec('bash /var/html/www/plc/bin/w1');
  $output = shell_exec('/var/www/html/plc/status/status');
  echo $output;
?>
