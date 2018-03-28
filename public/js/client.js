window.onload = function () {
    var loc =  window.location;
    var socket = io(loc.origin);
    var num_photos = 0;
    var cur_photo_id = 0;
    var dps = []; // dataPoints
    var chart = new CanvasJS.Chart("chartContainer", {
	      title :{
		        text: "Dynamic Distance"
	      },
	      axisY: {
		        includeZero: false
	      },
	      data: [{
		        type: "line",
		        dataPoints: dps
	      }]
    });

    var xVal = 0;
    var dataLength = 20; // number of dataPoints visible at any point

    socket.on('info', function (data) {
        console.log(data);
        var distance = data["distance"];
        var n = data["num_photos"];
        updateChart(distance);
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

    var updatePhoto = function(i) {
        //$("#img-holder").attr("src", get_photo_url(i));
        var new_url =  get_photo_url(i);
        console.log(new_url);
        document.getElementById("img-content").src= new_url;
    };

    var get_photo_url = function(i) {
        return "/photos/photo-" + i + ".jpeg";
    };

    var updateChart = function (yVal) {
		    dps.push({
			      x: xVal,
			      y: yVal
		    });

        xVal++;

	      if (dps.length > dataLength) {
		        dps.shift();
	      }

	      chart.render();
    };

}
