uniform sampler2D board_data_texture;
uniform sampler2D pixel_color_texture;
uniform sampler2D large_pixel_texture;

uniform float zoom_factor;
uniform float offset_x, offset_y;
uniform int board_width, board_height;
uniform int screen_width, screen_height;


void main(){
    vec2 nCoords = gl_TexCoord[0].xy;
    vec4 pixel = {0.1, 0.1, 0.1, 1.0};

    vec2 board_top_left_pos = {screen_width/2 - offset_x * zoom_factor,screen_height/2 - offset_y * zoom_factor};
    vec2 board_coords = {(nCoords.x * screen_width - board_top_left_pos.x)/(board_width*zoom_factor), (nCoords.y * screen_height - board_top_left_pos.y)/(board_height*zoom_factor)};

    if(board_coords.x >= 0 && board_coords.x <= 1 && board_coords.y >= 0 && board_coords.y <= 1){
        vec2 pixel_coords = {(board_coords.x * board_width - floor(board_coords.x * board_width))/257, (board_coords.y * board_height - floor(board_coords.y * board_height))};
        if(zoom_factor >= 32){
            pixel = texture2D(large_pixel_texture, vec2(texture2D(board_data_texture, board_coords).r + pixel_coords.x, pixel_coords.y));
        }else{
            if(texture2D(board_data_texture, board_coords).g > 1.0/255.0){//if electricity
                pixel = texture2D(pixel_color_texture, vec2(texture2D(board_data_texture, board_coords).r, 0.5f));
            }else{
                pixel = texture2D(pixel_color_texture, vec2(texture2D(board_data_texture, board_coords).r, 0));
            }
        }


    }

    gl_FragColor = pixel;
}