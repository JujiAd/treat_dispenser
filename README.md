# Wifi Enabled Treat Dispenser

This small repository provides everything needed to purchase, print, and prepare your own wifi enabled treat dispenser for remotely dispensing treats to our furry companions.

This project was created with the goal of integrating the functionality into a Home Assistant server (read more about that [here](https://www.home-assistant.io/)), but upon startup it creates it's own webserver that you can access from any device on the local network.

This was my first Arduino project and I relied heavily on the guides provided by [Random Nerd Tutorials](https://randomnerdtutorials.com/), specifically [ESP32 with Stepper Motor (28BYJ-48 and ULN2003 Motor Driver)](https://randomnerdtutorials.com/esp32-stepper-motor-28byj-48-uln2003/). If you would like to fork this project and are looking for inspiration, they provide a huge resource of proof-of-concept projects utilizing the ESP32 Dev Board to facilitate wifi-enabled projects.

# 3D model

```stl
solid cube_corner
  facet normal 0.0 -1.0 0.0
    outer loop
      vertex 0.0 0.0 0.0
      vertex 1.0 0.0 0.0
      vertex 0.0 0.0 1.0
    endloop
  endfacet
  facet normal 0.0 0.0 -1.0
    outer loop
      vertex 0.0 0.0 0.0
      vertex 0.0 1.0 0.0
      vertex 1.0 0.0 0.0
    endloop
  endfacet
  facet normal -1.0 0.0 0.0
    outer loop
      vertex 0.0 0.0 0.0
      vertex 0.0 0.0 1.0
      vertex 0.0 1.0 0.0
    endloop
  endfacet
  facet normal 0.577 0.577 0.577
    outer loop
      vertex 1.0 0.0 0.0
      vertex 0.0 1.0 0.0
      vertex 0.0 0.0 1.0
    endloop
  endfacet
endsolid
```

# Necessary Materials

All of the following links are suggestions - any equivalent piece of hardware will suffice. I tried to provide a link for all major components for the sake of providing a comprehensive resource, but any hardware you have lying around will do just as well.

## Electronics

ESP32 Dev Board - https://www.amazon.com/dp/B08D5ZD528?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1<br>
ULN2003 5V Stepper Motor and Driver Board - https://www.amazon.com/dp/B0BG4ZCFLQ?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1<br>
Jumper Cables - https://www.amazon.com/dp/B01EV70C78?ref=ppx_yo2ov_dt_b_fed_asin_title<br>
LEDs - https://www.amazon.com/dp/B07PG84V17?ref=ppx_yo2ov_dt_b_fed_asin_title<br>

## Hardware

Threaded Inserts - https://www.amazon.com/dp/B0D1CGC18H?ref=ppx_yo2ov_dt_b_fed_asin_title<br>
Metric Hex Screws, Nuts, and Washers - https://www.amazon.com/gp/product/B07K1DV93T/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1<br>

## Printer

3D Printer - [Any model will work, but I used the Bambulab P1S](https://us.store.bambulab.com/products/p1s?variant=42153262743688&srsltid=AfmBOorV5aYzq4TwLaTO3VjpY8YvXU3_rQGS1eiNNoLS8Y6xKWy6kxXf)

## Comments

- A design constraint I imposed on this project from the begining was that the entire finished product shoudl fit within a 5" diameter circle. I did this for aesthetic reasons, and because I wanted to use a [plant stand](https://www.amazon.com/dp/B07DKPQ5D1?ref=ppx_yo2ov_dt_b_fed_asin_title) to hold this finished product.
- The body of the treat dispenser was designed to accomodate the specific hardware I used (linked above). While the ESP32 and Driver Board are simply glued into place, the Stepper Motor dimensions did dictate the design of the mounting point in the treat dispenser body.
- I decided to setup this project using HTTPS POST requests as the driving mechanism for dispensing treats because that was the most easily expandable method. Once the treat dispenser is on and the webserver initialized, it will respond to the POST request from any source, which made it very easy to integrate into my Home Assistant server.
