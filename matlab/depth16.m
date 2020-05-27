clear
clc

no_frames = 1500;
no_video = 12;

images = cell(no_frames,1);
final_images = cell(no_frames,1);
parfor i = 0: no_frames - 1
    images{i+1} = imread(strcat(string(no_video),'/depth/', string(i), '.png')); 
end

mkdir(strcat(string(no_video),'/depthRaw'));
mkdir(strcat(string(no_video),'/depthFiltered'));
parfor k = 1:no_frames
    img = images{k};
    up = img(:,:,3);
    low = img(:,:,2);
    cnct_up = bitsll(uint16(up), 8);
    cnct_low = uint16(low);
    cnct = bitor(cnct_up, cnct_low);
    final_images{k} = cnct;
    imwrite(final_images{k},strcat(string(no_video),'/depthRaw/', string(k-1), '.png'));
    imwrite(imalign(final_images{k}, "floor"),strcat(string(no_video),'/depthFiltered/', string(k-1), '.png'));
end
