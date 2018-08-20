var StepperMotor = require("StepperMotor");

var motor = new StepperMotor({
  pins:[D12, D4, D14, D5]
});

function move() {
  // Move to step 100 in 1 second
motor.moveTo(100, 1000, function() {
  // Move back to step 0 in 0.5 seconds
  motor.moveTo(0, 500, function() {
    // we're done!
    console.log("Done!");
  }, true);  
});
}
