<?php

// watchman
if()

date_default_timezone_set('Africa/Nairobi');

$date = date('m/d/Y h:i:s a', time());
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1,maximum-scale=1">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/lykmapipo/themify-icons@0.1.2/css/themify-icons.css">
    <link rel="stylesheet" href="styles.css">
    <title>IRSS</title>
</head>
<body>

    <input type="checkbox" id="sidebar-toggle">
    <div class="sidebar">
        <div class="sidebar-header">
            <h3 class="brand">
                <span class="ti-plug"></span>
                <span>Robotic Arm</span>
            </h3>
            <label for="sidebar-toggle" class="ti-menu-alt"></label>
        </div>

        <div class="sidebar-menu">
            <ul>
                <li>
                    <a href="">
                        <span class="ti-layout-grid2"></span>
                        <span>Dashboard</span>
                    </a>
                </li>

                <li>
                    <a href="./controls.php">
                        <span class="ti-settings"></span>
                        <span>Controls</span>
                    </a>
                </li>

                <li>
                    <a href="./abt.php">
                        <span class="ti-book"></span>
                        <span>About</span>
                    </a>
                </li>

                <li>
                    <a href="">
                        <span class="ti-user"></span>
                        <span>Logout</span>
                    </a>
                </li>

            </ul>
        </div>
    </div>


<div class="main-content">

    <header>
        <div class="search-wrapper">
            <span class="ti-search"></span>
            <form action="search.php" method="post">
                <input type="search" placeholder="Search">
            </form>
            
        </div>

        <div class="social-icons">
<!--            <span class="ti-bell"></span>-->
<!--            <span class="ti-comment"></span>-->
            <div></div>
        </div>
    </header>

    <main>

        <h2 class="dash-title">Operation Statistics</h2>
        <small class="ferarri">Time: <?php echo $date; ?> </small>

        <div class="dash-cards">
<!--            OPERATION STATUS-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-power-off"></span>
                    <div>
                        <h5>Arm Status</h5>
                        <h4 id="status">Offline</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <a href="#" onclick="toggleMode();" id="change-op-mode">Start</a>
                </div>
            </div>

<!--            NUMBER OF OBJECTS-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-package"></span>
                    <div>
                        <h5>Capacity</h5>
                        <h4>50</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <!--<a href="">View all</a>-->
                </div>
            </div>

            <div class="card-single">
                <div class="card-body">
                    <span class="ti-archive"></span>
                    <div>
                        <h5>Picked objects</h5>
                        <h4>7</h4>
                    </div>
                </div>
                <div class="card-footer">
                   <!--<a href="">View all</a>-->
                </div>
            </div>

            <div class="card-single">
                <div class="card-body">
                    <span class="ti-control-pause"></span>
                    <div>
                        <h5>Remaining objects</h5>
                        <h4>43</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <!--<a href="">View all</a>-->
                </div>
            </div>

<!--            MOTOR SPEED-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-loop"></span>
                    <div>
                        <h5>Nominal Motor Speed</h5>
                        <h4>2 deg/s</h4>
                    </div>
                </div>
                <div class="card-footer">
<!--                    <a href="">View all</a>-->
                </div>
            </div>

<!--            OPERATION LOCATION-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-target"></span>
                    <div>
                        <h5>Operation Location</h5>
                        <h4>Main Loading Dock</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <a href="">View all</a>
                </div>
            </div>
        </div>
    </main>

</div>


<script src="main.js"></script>
</body>

</html>