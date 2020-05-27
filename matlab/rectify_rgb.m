clear
clc

no_frames = 1500;
no_video = 12;

images = cell(no_frames,1);
final_images = cell(no_frames,1);
for i = 0: no_frames - 1
    images{i+1} = imread(strcat(string(no_video),'/rgb/', string(i), '.png')); 
end

mkdir(strcat(string(no_video),'/rgbR'));


%do NOT parallelize this: memory issues occur
for k = 1:no_frames
    img = images{k};
    final_images{k} = imdistort(img, 320, 240, -0.050583743, 0.06607867, 0);
    imwrite(final_images{k},strcat(string(no_video),'/rgbR/', string(k-1), '.png'));
end
