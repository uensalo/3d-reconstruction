function rectified = imdistort(image, cx, cy, kappa_1, kappa_2, kappa_3)
    image = double(image);
    w = size(image, 2);
    h = size(image, 1);
    output_points = zeros(w * h, 5); % x y r g b
    k = 1;
    for j = 1:w
        for i = 1:h
            r2 = ((i - cy)/h)^2 + ((j - cx)/w)^2;
            distortion_coefficient = ( 1 + kappa_1 * r2 + kappa_2 * r2^2 + kappa_3 * r2^3 );
            jc = j * distortion_coefficient;
            ic = i * distortion_coefficient;
            point = [jc, ic, image(i,j,1), image(i,j,2), image(i,j,3)];
            output_points(k, :) = point;
            k = k + 1;
        end
    end
    
    rectified = zeros(size(image));
    for i = 1: w * h
        x1 = max(floor(output_points(i,2)), 1);
        x2 = min(h, x1 + 1);

        y1 = max(floor(output_points(i,1)), 1);
        y2 = min(w, y1 + 1);
        
        if(x1 > h || x2 > h || y1 > w || y2 > w || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
            continue;
        end

        kx = (x2 - output_points(i,2));
        ky = (y2 - output_points(i,1));

        rectified(x1,y1,1) = rectified(x1,y1,1) + kx * ky * output_points(i,3);
        rectified(x1,y1,2) = rectified(x1,y1,2) + kx * ky * output_points(i,4);
        rectified(x1,y1,3) = rectified(x1,y1,3) + kx * ky * output_points(i,5);
        
        
        rectified(x2,y1,1) = rectified(x2,y1,1) + (1 - kx) * ky * output_points(i,3);
        rectified(x2,y1,2) = rectified(x2,y1,2) + (1 - kx) * ky * output_points(i,4);
        rectified(x2,y1,3) = rectified(x2,y1,3) + (1 - kx) * ky * output_points(i,5);
        
        rectified(x1,y2,1) = rectified(x1,y2,1) + kx * (1 - ky) * output_points(i,3);
        rectified(x1,y2,2) = rectified(x1,y2,2) + kx * (1 - ky) * output_points(i,4);
        rectified(x1,y2,3) = rectified(x1,y2,3) + kx * (1 - ky) * output_points(i,5);
        
        rectified(x2,y2,1) = rectified(x2,y2,1) + (1 - kx) * (1 - ky) * output_points(i, 3);
        rectified(x2,y2,2) = rectified(x2,y2,2) + (1 - kx) * (1 - ky) * output_points(i, 4);
        rectified(x2,y2,3) = rectified(x2,y2,3) + (1 - kx) * (1 - ky) * output_points(i, 5);
    end
    rectified = double(rectified/255);
end