img = uint8(255 * (rgb2gray(im2double(imread("lel.jpeg")))));

img_low =  bitsll(bitand(img,uint8(7)), 4);
img_high = bitsrl(bitand(img,uint8(1)), 4);

imfinal = bitor(img_low,img_high);

imwrite(imfinal, "gf.png");