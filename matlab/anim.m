clear
clc

image = imread('9/depthG/380.png');
[depth, cloud] = point_cloud_from_depth_image(image);
figure
for i = pi : 0.3 : 2 * pi
    for j = pi : 0.3 : pi
        for k = pi : 0.3 : 2 * pi
            imshow(render_point_cloud(depth,cloud, eul2rotm([i j k]), [i * 20000;j * 20000; k * 20000]));
        end
    end
end

function [point_depth, point_cloud] = point_cloud_from_depth_image(im)
    pixel_array_w_depth = 640;
    sensor_w_depth = 3.2;
    depth_mm_to_pixel = pixel_array_w_depth / sensor_w_depth;
    depth_intrinsics_flat = [546.85474, 546.1455, 321.0402, 224.9638];

    depth_rotation = [-0.00559971751097979, -0.999942398639151, 0.00673094560580176;
                      -0.999858918907729, 0.00553924975686035, -0.0146064686118277;
                      0.0145687509977038, -0.00681219850147312, -0.999832339536000];
    depth_translation = [-0.0105528645000000 * depth_mm_to_pixel; 0.00175728080000000 * depth_mm_to_pixel; 0];
        mask = uint16(65528);
    im = double(bitsrl(bitand(im, mask),3));


    points = zeros(3, 480 * 640);
    k = 1;
    for u = 1:480
        for v = 1:640
            Z = im(u,v) * depth_mm_to_pixel;
            point = [(v - depth_intrinsics_flat(3)) / depth_intrinsics_flat(1) * Z;
                     (u - depth_intrinsics_flat(4)) / depth_intrinsics_flat(2) * Z;
                     Z];
            points(:,k) = depth_rotation' * (point - depth_rotation' * depth_translation);
            k = k + 1;
        end
    end
    point_cloud = points;
    point_depth = -points(3,:) / depth_mm_to_pixel;
end

function final_image = render_point_cloud(depth, points, camera_rotation, camera_position)
    pixel_array_w_color = 640;
    pixel_array_h_color = 480;
    color_intrinsics = [514.4141, 0, 318.7396;
                        0, 513.2003, 240.3392;
                        0, 0, 1];
    color_rotation = camera_rotation;
    color_translation = camera_position;

    points = color_intrinsics * ((color_rotation * points) + color_translation);
    points = points ./ points(3,:);

    points_f = zeros(size(points));
    for i = 1: 640 * 480
        if(points(1,i) >= 0 && points(1,i) <= pixel_array_w_color && points(2,i) >= 0 && points(2,i) <= pixel_array_h_color)
            points_f(:,i) = points(:,i);
            points_f(3,i) = depth(i);
        end
    end

    final_image = zeros(480,640);

    for i = 1: 480 * 640
       final_image( 1 + floor(points_f(2,i)), 1 + floor(points_f(1,i))) = points_f(3,i);
    end
    final_image = uint16(final_image);
    final_image = bitsll(final_image,3);
end


