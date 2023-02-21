$(document).ready(function()
{
  $.ajax(
  {
    url: "http://localhost/data.php",
    method: "GET",
    success: function(data) 
	{
      console.log(data);
      var time = [];
      var Rain = [];

      for(var i in data) 
	  {
        time.push(data[i].Time);
        Rain.push(data[i].Rain);
      }

      var chartdata = 
	  {
        labels: time,
        datasets : [
          {
            label: 'Time Rain',
            backgroundColor: 'rgba(200, 200, 200, 0.75)',
            borderColor: 'rgba(200, 200, 200, 0.75)',
            hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
            hoverBorderColor: 'rgba(200, 200, 200, 1)',
            data: Rain
          }
        ]
      };

      var ctx = $("#mycanvas");

      var barGraph = new Chart(ctx, 
	  {
        type: 'bar',
        data: chartdata
      });
    },
    error: function(data) 
	{
      console.log(data);
    }
  });
	setTimeout(function(){
	window.location.reload(1);
	}, 5000);
});



