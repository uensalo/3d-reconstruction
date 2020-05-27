clear
clc

%color = imdistort(imread('9/rgb/1002.png'), 320, 240, -0.050583743, 0.06607867, 0); 
img = imread('12/depthRaw/1002.png');
d = imalign(imread('12/depthFiltered/1002.png'), "floor");

figure
imshow(img);

figure
imshow(d);