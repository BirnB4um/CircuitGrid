uniform sampler2D board_data_texture;
uniform sampler2D pixel_color_texture;

uniform float zoom_factor;
uniform float offset_x, offset_y;
uniform int board_width, board_height;
uniform int screen_width, screen_height;


void main(){
    vec2 nCoords = gl_TexCoord[0].xy;
    vec4 pixel = {0.1, 0.1, 0.1, 1.0};

    vec2 board_top_left_pos = {screen_width/2 - offset_x * zoom_factor,screen_height/2 - offset_y * zoom_factor};
    vec2 new_coords = {(nCoords.x * screen_width - board_top_left_pos.x)/(board_width*zoom_factor), (nCoords.y * screen_height - board_top_left_pos.y)/(board_height*zoom_factor)};

    if(new_coords.x > 0 && new_coords.x < 1 && new_coords.y > 0 && new_coords.y < 1){
        pixel = texture2D(pixel_color_texture, vec2(texture2D(board_data_texture, new_coords).r,0));
        if(texture2D(board_data_texture, new_coords).g > 1.1/255){//if electricity
            pixel.r += 0.3;
        }
    }

    gl_FragColor = pixel;
}