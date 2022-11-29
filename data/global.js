document.addEventListener("DOMContentLoaded",(event)=>{
    console.log("ready",event)
    init();
})

var card;
var s;
function init(){
    card = document.getElementById("pump");    
    card.addEventListener("click", toggle_status);
    s = card.getAttribute("data-status")
    console.log(s);
}

function toggle_status(e){
    console.log(e);
    s = card.getAttribute("data-status") 
    if(s=="on"){
        //card.setAttribute("data-status","off");
        document.location.href = "/?pump_status=off";
    }else{
        //card.setAttribute("data-status","on")
        document.location.href = "/?pump_status=on";
    }
    console.log(s);
}