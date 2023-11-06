const audio = document.getElementById("myAudio");
audio.muted = false;
audio.addEventListener("ended", function () {
    audio.currentTime = 0; // Reset the audio to the beginning
    audio.play(); // Start playing again
});
const rainbowColors = [
    "#FF0000", // Red
    "#FF7F00", // Orange
    "#FFFF00", // Yellow
    "#00FF00", // Green
    "#0000FF", // Blue
    "#4B0082", // Indigo
    "#9400D3"  // Violet
];

let currentIndex = 0;

function changeBackgroundColor() {
    document.body.style.transition = "background-color 0.2s"; // Smooth transition
    document.body.style.backgroundColor = rainbowColors[currentIndex];
    currentIndex = (currentIndex + 1) % rainbowColors.length;
}

setInterval(changeBackgroundColor, 200);
