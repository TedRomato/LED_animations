
# LED_animations
  <h1>Code for basic led animation using shift registers 74hc595.</h1>

  <p>This repository contains code for simple LED animation, which can be changed using push button.</p>
  <img src="https://user-images.githubusercontent.com/59472129/112056503-5f77c600-8b58-11eb-8b6d-079e080e2b79.gif">
  <h2>Code:</h2>
  <p>Code including comments is in LED_patterns_uint16_t.ino file.</p>
  <p>If you would like to create your own animation, you can use premade functions. Just add case into switch in loop function, and write your animation there. Then you also     have to change patternAmount variable to match amount of cases.</p>
  <h3>Here is function list</h3>
  <ul>
    <li>powerLEDs()</li>
    <li>graduallyChange()</li>
    <li>graduallyChangeHalves()</li>
    <li>spinPattern()</li>
  </ul>

  <h2>Circuit:</h2>
  <img src="https://github.com/TedRomato/LED_animations/blob/master/circuit.png" width="480px">
  <h3>Components:</h3>
  <p>
    <ul>
      <li>Arduino UNO</li>
      <li>2x 74hc595 shift registers</li>
      <li>555 Timer</li>
      <li>14 red LED's</li>
      <li>14 330 Ohm resistors</li>
      <li>Push button</li>
      <li>1k Ohm resistor</li>
      <li>10k Ohm resistor</li>
      <li>Cables</li>
      <li>Another red diode and 330 Ohm resistor (not compulsory)</li>
    </ul>
  </p>
  <h3>Wiring:</h3>
  <p>This project has 3 main parts:</p>
  <ul>
    <li>Shift registers</li>
    <li>Diodes</li>
    <li>Push button with one bit memory</li>
  </ul>
  <p>First we put down our Shift registers, and wire them according to diagram. Then we put down our diodes in parallel. Don't forget to add your 330 Ohm resistors, before every diode, so it doesn't overload. Then wire your first diode to pin Q7 of second shift register (the one that does't have DO connected). Then connect the rest. On the diagram, diodes are indexed from bottom up. After connecting our diodes with our shift registers, we go on and put down our animation change push button, with 555 Timer according to diagram (top left corner). <br> Not Compulsory step: If you would like to see, when push button was pressed, and change of animation is about to occur, just connect another red LED with 330 Ohm resistor from 555 Timer OUT pin to ground. Now, if the diode is on, you know that animation is about to change.</p>
  






