let cafes = {};

function Add(){
  let cafeName = prompt("Enter cafe name:");
  let cafeInfo = prompt("Enter cafe info:");

  if(cafeName && cafeInfo){
    cafes[cafeName] = cafeInfo;
    console.log("Cafe " + cafeName + " was added!");
  }
  else{
    alert("Cafe name and info are required!");
  }
}

function Delete(){
  let cafeNameToDelete = prompt("Enter cafe name to delete:");

  if(cafeNameToDelete){
    delete cafes[cafeNameToDelete];
    console.log("Cafe " + cafeNameToDelete + " was deleted!");
  }
  else{
    alert("Cafe name is required!");
  }
}

function Receive(){
  let cafeName = prompt("Enter cafe name:");

  if(cafeName){
    if(cafeName in cafes){
      console.log(cafes[cafeName]);
    }
    else{
      console.log("Cafe not found!");
    }
  }
  else{
    alert("Cafe name is required!");
  }
}

function ReceiveAll(){
  let size = Object.keys(cafes).length;

  if(size == 0){
    console.log("No cafes!");
  }
  else{
    for(let cafeName in cafes){
      console.log("Cafe:" + cafeName + " Info:" + cafes[cafeName]);
    }
  }
}

