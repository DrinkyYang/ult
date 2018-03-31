window.onload = function () {
    var loc =  window.location;
    var socket = io(loc.origin);
    var num_photos = 0;
    var cur_photo_id = 0;
    var distance_dps = []; // dataPoints
    var speed_dps = []; // dataPoints
    var distance_chart = new CanvasJS.Chart("DistancechartContainer", {
	      title :{
		        text: "Dynamic Distance"
	      },
	      axisY: {
		        includeZero: false
	      },
	      data: [{
		        type: "line",
		        dataPoints: distance_dps
	      }]
    });
    var speed_chart = new CanvasJS.Chart("SpeedchartContainer", {
	      title :{
		        text: "Dynamic Speed"
	      },
	      axisY: {
		        includeZero: false
	      },
	      data: [{
		        type: "line",
		        dataPoints: speed_dps
	      }]
    });


    var xVal = 0;
    var dataLength = 20; // number of dataPoints visible at any point

	  distance_chart.render();
	  speed_chart.render();

    socket.on('info', function (data) {
        console.log(data);
        var distance = data["distance"];
        var speed = data["speed"];
        var n = data["num_photos"];
        updateChart(distance, speed);
        if (n > num_photos) {
            num_photos = n;
            updatePhoto(n);
        }
    });


    var prev_button = document.getElementById('prev-b');

    prev_button.addEventListener('click', function() {
        if (cur_photo_id > 0) {
            console.log("prev");
            cur_photo_id = cur_photo_id - 1;
            updatePhoto(cur_photo_id);
        }
    });

    var next_button = document.getElementById('next-b');

    next_button.addEventListener('click', function() {
        if (cur_photo_id < num_photos) {
            console.log("next");
            cur_photo_id = cur_photo_id + 1;
            updatePhoto(cur_photo_id);
        }
    });


    var set_button = document.getElementById('set-b');
    set_button.addEventListener('click', function() {
        var max_distance = document.getElementById('distance-conf').value;
        var max_speed = document.getElementById('speed-conf').value;
        console.log(max_distance);
        console.log(max_speed);
        socket.emit("set", {max_distance: max_distance, max_speed: max_speed});
    });

    var updatePhoto = function(i) {
        //$("#img-holder").attr("src", get_photo_url(i));
        var new_url =  get_photo_url(i);
        console.log(new_url);
        document.getElementById("img-content").src= new_url;
    };

    var get_photo_url = function(i) {
        return "/photos/photo-" + i + ".jpeg";
    };

    var updateChart = function (distance, speed) {
		    distance_dps.push({
			      x: xVal,
			      y: distance
		    });
		    speed_dps.push({
			      x: xVal,
			      y: speed
		    });

        xVal++;

	      if (distance_dps.length > dataLength) {
		        distance_dps.shift();
		        speed_dps.shift();
	      }

	      distance_chart.render();
	      speed_chart.render();
    };

}
