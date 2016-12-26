let mainWrapper = document.querySelector('#notifications');

let socket = io();

socket.on('texts',function(data){
	console.log(data);
	for(texts of data){
		let newDiv = document.createElement('div');
		newDiv.classList.add('texts');
		newDiv.dataset.id = image.id;
		let text  = document.createElement('p');
		text.src = texts.src;
		newDiv.appendChild(texts);
		mainWrapper.appendChild(newDiv);
	}
});

socket.on('toScreen', function (data) {
	console.log(data);
	document.getElementById("m_space").innerHTML = data.m;
	memory = data.m;
	
});

// socket.on('numOfImgs', function(data){
// 	console.log("number of images in folder is :" ,data);

// 	var myImages = document.getElementById('imageContainer');
// 	//for(let i=0; i<images.length; i++){
// 	for(let i=0; i< data; i++){
// 		//create img tags 
// 		// <img src="">
// 		var newDiv = document.createElement("div");
// 		newDiv.setAttribute("id", "images");

// 		var newImage = new Image();
// 		newImage.src="data/image" + i + ".jpg";
// 		console.log(newImage.src);
// 		newDiv.appendChild(newImage);
// 		myImages.appendChild(newDiv);
// 	}
// });



//When color button is clicked emit data to socket

	function toServer(){

		var mval = document.getElementById('mval').value;
		socket.emit('toArduino', {x:"capture"});
	}
