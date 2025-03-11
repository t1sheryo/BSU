class THashStorage{
  cafes = {};

  Reset(){
    this.cafes = {};
    console.log("Cafes Hash was successfully reset!");
  }

  Add(){
    let cafeName = prompt("Enter cafe name:");
    let cafeInfo = prompt("Enter cafe info:");
  
    if(cafeName && cafeInfo){
      this.cafes[cafeName] = cafeInfo;
      console.log("Cafe " + cafeName + " was added!");
    }
    else{
      alert("Cafe name and info are required!");
    }
  }

  GetValue(){
    let cafeName = prompt("Enter cafe name:");
  
    if(cafeName){
      if(cafeName in this.cafes){
        console.log(this.cafes[cafeName]);
      }
      else{
        console.log("Cafe not found!");
      }
    }
    else{
      alert("Cafe name is required!");
    }
  }

  Delete(){
    let cafeNameToDelete = prompt("Enter cafe name to delete:");
  
    if(cafeNameToDelete){
      delete this.cafes[cafeNameToDelete];
      console.log("Cafe " + cafeNameToDelete + " was deleted!");
    }
    else{
      alert("Cafe name is required!");
    }
  }

  GetKeys(){
    let size = Object.keys(this.cafes).length;
  
    if(size == 0){
      console.log("No cafes!");
    }
    else{
      let i = 1;
      for(let cafeName in this.cafes){
        console.log("Key " + i + ": " + this.cafes[cafeName]);
        i++;
      }
    }
  }
}