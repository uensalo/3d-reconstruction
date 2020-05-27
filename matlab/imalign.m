function final_image = imalign(im, interp_option)
    pixel_array_w_color = 640;
    pixel_array_h_color = 480;

    pixel_array_w_depth = 640;
    pixel_array_h_depth = 480;
    
    
    sensor_w_depth = 3.2;
    sensor_h_depth = 2.4;

    sensor_w_color = 5.645;
    sensor_h_color = 4.234;

    depth_mm_to_pixel = pixel_array_w_depth / sensor_w_depth;
    
    depth_intrinsics_flat = [535.85474, 535.1455, 321.0402, 224.9638];

    depth_intrinsics = [546.85474, 0, 321.0402;
                        0, 546.1455, 224.9638;
                        0, 0, 1];
    depth_rotation = [-0.00559971751097979, -0.999942398639151, 0.00673094560580176;
                      -0.999858918907729, 0.00553924975686035, -0.0146064686118277;
                      0.0145687509977038, -0.00681219850147312, -0.999832339536000];

    depth_translation = depth_mm_to_pixel * [10.5528645; 1.7572808; 0];
    %{

    color_intrinsics_flat = [3199.3523, 3196.6003, 2043.9598, 1504.7074];                
    color_intrinsics = [3199.3523, 0, 2043.9598;
                        0, 3196.6003, 1504.7074;
                        0, 0, 1];
    color_rotation = [0, -1, 0;
                      -1, 0, 0;
                      0,0,-1];
    color_translation = [0;0;0];
    %}


    color_intrinsics_flat = [514.4141, 513.2003, 318.7396, 240.3392];
    color_intrinsics = [514.4141, 0, 318.7396;
                        0, 513.2003, 240.3392;
                        0, 0, 1];
    color_rotation = [0, -1, 0;
                      -1, 0, 0;
                      0,0,-1];
    color_translation = [0;0;0];
    
    kappa_1_depth = 0.06442407;
    kappa_2_depth = 0.21935692;
    kappa_3_depth = -0.5105902;
    
    kappa_1_color = -0.050583743;
    kappa_2_color = 0.06607867;
    kappa_3_color = 0;

    mask = uint16(65528);
    im = double(bitsrl(bitand(im, mask),3));


    points = zeros(3, 480 * 640);
    k = 1;
    for u = 1:480
        for v = 1:640
            r2 = ((depth_intrinsics_flat(4)-u)/480)^2 + ((depth_intrinsics_flat(3)-v)/640)^2;
            uc = u * ( 1 + kappa_1_depth * r2 + kappa_2_depth * r2^2 + kappa_3_depth * r2^3 );
            vc = v * ( 1 + kappa_1_depth * r2 + kappa_2_depth * r2^2 + kappa_3_depth * r2^3 );
            %uc = u;
            %vc = v;
            
            Z = im(u,v) * depth_mm_to_pixel;
            point = [(vc - depth_intrinsics_flat(3)) / depth_intrinsics_flat(1) * Z;
                     (uc - depth_intrinsics_flat(4)) / depth_intrinsics_flat(2) * Z;
                     Z];
            points(:,k) = depth_rotation' * (point - depth_rotation' * depth_translation);
            k = k + 1;
        end
    end
    
    points_depth = -points(3,:) / depth_mm_to_pixel;
    
    points_in_color_camera_space = ((color_rotation * points) + color_translation);
    projected_points = color_intrinsics * points_in_color_camera_space;
    projected_points = projected_points ./ projected_points(3,:);
    

    points_f = zeros(size(projected_points));
    for i = 1: 640 * 480
        if(projected_points(1,i) >= 0 && projected_points(1,i) <= pixel_array_w_color && projected_points(2,i) >= 0 && projected_points(2,i) <= pixel_array_h_color && points_depth(i) > 0)
            points_f(:,i) = projected_points(:,i);
            points_f(3,i) = norm(points_in_color_camera_space(:,i) / depth_mm_to_pixel);
        end
    end

    final_image = zeros(480,640);
    
    if (interp_option == "bilinear")
        
        for i = 1: 480 * 640
            x1 = max(floor(points_f(2,i)), 1);
            x2 = min(480, x1 + 1);

            y1 = max(floor(points_f(1,i)), 1);
            y2 = min(640, y1 + 1);

            kx = (x2 - points_f(2,i));
            ky = (y2 - points_f(1,i));

            final_image(x1,y1) = final_image(x1, y1) + kx * ky * points_f(3,i);
            final_image(x2,y1) = final_image(x2, y1) + (1 - kx) * ky * points_f(3,i);
            final_image(x1,y2) = final_image(x1, y2) + kx * (1 - ky) * points_f(3,i);
            final_image(x2,y2) = final_image(x2, y2) + (1 - kx) * (1 - ky) * points_f(3,i);
        end
        
    else 
        for i = 1: 640 * 480
            final_image(floor(points_f(2,i)) + 1, floor(points_f(1,i)) + 1) = floor(points_f(3,i));
        end
    end
    final_image = medfilt2(final_image);
    final_image = uint16(final_image);
    final_image = bitsll(final_image,3);
end


