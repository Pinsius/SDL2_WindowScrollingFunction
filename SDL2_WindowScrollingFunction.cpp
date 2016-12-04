/**
TextTexture is name of my class that holds an info about text Rect and SDL_Texture
    So : _rect - private variable of type SDL_Rect
        _texture - SDL_Texture*
**/

void TextTexture::write(SDL_Renderer* renderer,int& windowHeight,int& maxHeight,float* window_camera){
    // I dont want to change the original SDL_Rect struct so im going to make a temporary copy
    SDL_Rect outRect = _rect;

    //Offseting my texture using the window_camera param
    outRect.y = _rect.y - *window_camera;
   if (outRect.y<windowHeight){
        //In case the texture Y is bigger than the minimum Y
        int pos_y = windowHeight-outRect.y;

        //Setting the inner Rect(the cropped area)
        SDL_Rect inRect = {0 ,pos_y,_rect.w,_rect.h};

        //Modyfing the outRect
        outRect.h -=pos_y;
        outRect.y +=pos_y;

        //_texture is a texture used for "scroll cropping"
        SDL_RenderCopy(renderer,_texture,&inRect,&outRect);

   } else if (outRect.y+outRect.h>maxHeight){
        //In case the texture Y is bigger than the maxHeight

        //Setting the inner Rect(the cropped area)
        SDL_Rect inRect = {0 ,0,_rect.w,maxHeight-outRect.y};

        //Modifying the outRect
        outRect.h = maxHeight-outRect.y;
        outRect.y -= (outRect.y+outRect.h)-maxHeight;

        //_texture is a texture used for "scroll cropping"
        SDL_RenderCopy(renderer,_texture,&inRect,&outRect);
   } else {
        //Normal render
        SDL_RenderCopy(renderer,_texture,NULL,&outRect);
   }
}
