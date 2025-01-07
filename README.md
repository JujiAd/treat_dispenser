# Wifi Enabled Treat Dispenser

This small repository provides everything needed to purchase, print, and prepare your own wifi enabled treat dispenser for remotely dispensing treats to our furry companions.

This project was created with the goal of integrating the functionality into a Home Assistant server (read more about that [here](https://www.home-assistant.io/)), but upon startup it creates it's own webserver that you can access from any device on the local network.

This was my first Arduino project and I relied heavily on the guides provided by [Random Nerd Tutorials](https://randomnerdtutorials.com/), specifically [ESP32 with Stepper Motor (28BYJ-48 and ULN2003 Motor Driver)](https://randomnerdtutorials.com/esp32-stepper-motor-28byj-48-uln2003/). If you would like to fork this project and are looking for inspiration, they provide a huge resource of proof-of-concept projects utilizing the ESP32 Dev Board to facilitate wifi-enabled projects.

# 3D model

![Treat Dispenser](https://github.com/JujiAd/treat_dispenser/raw/main/design/v0/resources/full_body.JPG)

```stl
solid Mesh
  facet normal 0.293276 -0.955848 0.018565
    outer loop
      vertex 20.313026 -61.769737 -13.338286
      vertex 20.317863 -61.768154 -13.333190
      vertex 17.848860 -62.526222 -13.360068
    endloop
  endfacet
  facet normal 0.293584 -0.955655 -0.023044
    outer loop
      vertex 18.620382 -62.284710 -13.546476
      vertex 20.313026 -61.769737 -13.338286
      vertex 17.848860 -62.526222 -13.360068
    endloop
  endfacet
  facet normal 0.300173 -0.949439 -0.091984
    outer loop
      vertex 20.065918 -61.823456 -13.590206
      vertex 20.313026 -61.769737 -13.338286
      vertex 18.620382 -62.284710 -13.546476
    endloop
  endfacet
  facet normal 0.289317 -0.928693 -0.232003
    outer loop
      vertex 18.609283 -62.240761 -13.736242
      vertex 20.065918 -61.823456 -13.590206
      vertex 18.620382 -62.284710 -13.546476
    endloop
  endfacet
  facet normal 0.290340 -0.911466 -0.291431
    outer loop
      vertex 19.808323 -61.826736 -13.836576
      vertex 20.065918 -61.823456 -13.590206
      vertex 18.609283 -62.240761 -13.736242
    endloop
  endfacet
  facet normal 0.274327 -0.885402 -0.375244
    outer loop
      vertex 18.590090 -62.170052 -13.917115
      vertex 19.808323 -61.826736 -13.836576
      vertex 18.609283 -62.240761 -13.736242
    endloop
  endfacet
  facet normal 0.266940 -0.833895 -0.483075
    outer loop
      vertex 19.545269 -61.774887 -14.071440
      vertex 19.808323 -61.826736 -13.836576
      vertex 18.590090 -62.170052 -13.917115
    endloop
  endfacet
  facet normal 0.257269 -0.820944 -0.509769
    outer loop
      vertex 18.563280 -62.074329 -14.084799
      vertex 19.545269 -61.774887 -14.071440
      vertex 18.590090 -62.170052 -13.917115
    endloop
  endfacet
  facet normal 0.233068 -0.735963 -0.635640
    outer loop
      vertex 18.529331 -61.955357 -14.234997
      vertex 19.545269 -61.774887 -14.071440
      vertex 18.563280 -62.074329 -14.084799
    endloop
  endfacet
endsolid Mesh
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
