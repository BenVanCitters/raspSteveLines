precision highp float;

uniform sampler2D tex0;
uniform vec2 resolution;

uniform float time;
uniform float hiCut;
uniform float lowCut;
varying float col;


void main(void)
 {
    // texture offsetting and mirroring
    vec2 texCoord = gl_FragCoord.xy / resolution.xy;
    texCoord.x *= 2.0;
    texCoord.x = 1.0- abs(1.0-texCoord.x);
    texCoord.y+= .25;
    texCoord.y *= 2.0;

   // gl_FragColor = vec4(col,col,col,1);
    vec4 tempColor = texture2D(tex0,texCoord.st);
    float brightness = (tempColor.r+tempColor.g+tempColor.b)/3.0;
float lCut = 0.0;
float hCut = 1.0*(sin(time/200.0)+1.0)/2.0;


//    if(brightness < hCut && brightness > lCut)
  //  {
//        //gl_FragColor = texture2D(tex0,texCoord.st);
//        gl_FragColor =tempColor;// vec4(0.2+1.5*tempColor.rgb,tempColor.r/2.0 +0.5);
//    }
//    else
//    {
//        gl_FragColor = vec4(1.0,0.0,0.0,0.0);
//    }
float two_pi = 3.141592*2.0;
float newR = (1.0+sin(time/4.0+tempColor.r*two_pi))/2.0;
float newG = (1.0+sin(time/4.0+tempColor.g*two_pi))/2.0;
float newB = (1.0+sin(time/4.0+tempColor.b*two_pi))/2.0;
float newA = (1.0+sin(time/4.0+5.0*(tempColor.r+tempColor.g+tempColor.b)))/2.0;
        gl_FragColor = vec4(newR,newG,newB,newA);
}    


