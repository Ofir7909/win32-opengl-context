#include <windows.h>
#include <glad\glad.h>

HDC dc;
HGLRC rc;

LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT msg,
                            WPARAM wParam,
                            LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            PIXELFORMATDESCRIPTOR pfd = { 
                sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
                1,                     // version number  
                PFD_DRAW_TO_WINDOW |   // support window  
                    PFD_SUPPORT_OPENGL |   // support OpenGL  
                    PFD_DOUBLEBUFFER,      // double buffered  
                PFD_TYPE_RGBA,         // RGBA type  
                24,                    // 24-bit color depth  
                0, 0, 0, 0, 0, 0,      // color bits ignored  
                0,                     // no alpha buffer  
                0,                     // shift bit ignored  
                0,                     // no accumulation buffer  
                0, 0, 0, 0,            // accum bits ignored  
                32,                    // 32-bit z-buffer      
                0,                     // no stencil buffer  
                0,                     // no auxiliary buffer  
                PFD_MAIN_PLANE,        // main layer  
                0,                     // reserved  
                0, 0, 0                // layer masks ignored  
            }; 
            dc = GetDC(hwnd);
            int pf = ChoosePixelFormat(dc, &pfd);
            SetPixelFormat(dc, pf, &pfd);
            rc = wglCreateContext(dc);
            wglMakeCurrent(dc, rc);
            gladLoadGL();
            glViewport(0, 0, 640, 480);
            MessageBoxA(0, glGetString(GL_VERSION), "OPENGL VERSION",0);
            return 0;
        } break;
        /*
        // WM_CLOSE
        case WM_CLOSE:
        {
            if(MessageBox(hwnd, L"Quit?", L"App", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            }
            return 0;
        } break;
        */
        case WM_DESTROY:
        {
            ReleaseDC(hwnd, dc);
            wglDeleteContext(rc);
            PostQuitMessage(0);
            return 0;
        } break;
        
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        } break;
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE pInstance,
                    PWSTR cmd,
                    int showCmd
                    )
{
    // test
    /*
   MessageBox(0, cmd, L"Test cmd", 0);
    
   wchar_t buffer[256];
   wsprintfW(buffer,
             L"showCmd: (%d)",
             showCmd);
    
   MessageBox(0, buffer, L"Test ", 0);
    
   OutputDebugStringA("\nHello\n");
    */
    // init app
    
    WNDCLASS wc = {0};
    
    const wchar_t CLASS_NAME[] = L"Tutorial";
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    
    RegisterClass(&wc);
    
    // create window
    
    HWND hwnd;
    
    int width = 640;
    int height = 480;
    RECT wr = {0, 0, width, height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    
    hwnd = CreateWindow(CLASS_NAME, CLASS_NAME,
                        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                        0,0,
                        wr.right - wr.left,
                        wr.bottom - wr.top,
                        0,0,hInstance,0);
    
    if(hwnd == NULL)
    {
        return 0;
    }
    
    ShowWindow(hwnd, showCmd);
    
    // game loop
    
    MSG msg = {0};
    
    int running = 1;
    
    while(running)
    {
        while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                running = 0;
            }
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // update, render
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapBuffers(dc);
    }
    
    return 0;
}