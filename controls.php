<?php

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
    <title>IRSS: Controls</title>
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
                <a href="">
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
<!--                <input type="search" placeholder="Search">-->
            </form>

        </div>

        <div class="social-icons">
            <!--            <span class="ti-bell"></span>-->
            <!--            <span class="ti-comment"></span>-->
            <div></div>
        </div>
    </header>

    <main>

        <h2 class="dash-title">Controls</h2>
        <small class="ferarri">Time: <?php echo $date; ?> </small>

        <div class="dash-cards">
            <!--            ARM ON OR OFF-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-power-off"></span>
                    <div>
                        <h5>Turn Motor ON or OFF</h5>
                        <h4 id="status">Offline</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <a href="#" onclick="toggleMode();" id="change-op-mode">Start</a>
                </div>
            </div>

            <!--            CHANGE MOTOR SPEED-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-package"></span>
                    <div>
                        <h5>Change Motor Speed</h5>
                        <small>Restart the arm to apply the changes</small>
                        <h4>Current Speed: </h4> <!--To fetch this speed from the cloud -->
                        <h4>10deg/s</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <a href="">-</a>
                    <a href="">+</a>
                </div>
            </div>

            <!--            CONVEYOR BELT OPERATIONS-->
            <div class="card-single">
                <div class="card-body">
                    <span class="ti-loop"></span>
                    <div>
                        <h5>Conveyor Belt and Camera</h5>
                        <h4>ON</h4>
                    </div>
                </div>
                <div class="card-footer">
                    <a href="">OFF</a>
                </div>
            </div>

        </div>
    </main>

</div>


<script src="main.js"></script>
</body>

</html>