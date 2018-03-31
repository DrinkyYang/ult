# Commnunication between Node.js and C.
- Simple and bad approach.
- Via disk file IO.
- see write.c

## Photos
- the Photos are saved in the directory of /public/photos/
- the file name should be photo-n.jpeg, e.g. photo-1.jpeg.
- n is the order that the photo is recorded. You can maintain a global value for `n`, and `n++` if you record a new photo, then name the photo as `photo-n.jpeg`.

# install Node.js in Pi
```
wget https://nodejs.org/dist/latest-v9.x/node-v9.9.0-linux-armv7l.tar.gz
tar -xvf node-v9.9.0-linux-armv7l.tar.gz 
sudo mv node-v9.9.0-linux-armv7l  /usr/local/node
sudo ln -s /usr/local/node/bin/node /usr/bin/node
sudo ln -s /usr/local/node/bin/npm /usr/bin/npm

```

# run nodejs service 

## install dependencies in the project directory
```
npm install 
```

## run
```
node app.js
```

# Browser
- visit http://10.20.199.138:5000/
- 10.20.199.138 is the IP of your Pi. Please modify it to yours.


# Setting
- max distance and max speed
- They were wrote in `/tmp/ult.conf` in format `%d, %d` (distance, speed).
- Please read and update them in your C code periodically.

