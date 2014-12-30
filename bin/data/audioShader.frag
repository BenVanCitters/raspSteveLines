precision highp float;

uniform sampler2D tex0;
uniform vec2 resolution;
varying float col;

void main(void)
 {
    vec2 texCoord = gl_FragCoord.xy / resolution.xy;
    texCoord.x *= 2.0;
    texCoord.x = 1.0- abs(1.0-texCoord.x);
    texCoord.y+= .25;
    texCoord.y *= 2.0;
   // gl_FragColor = vec4(col,col,col,1);
    vec4 tempColor = texture2D(tex0,texCoord.st);
    //gl_FragColor = texture2D(tex0,texCoord.st);
    gl_FragColor = vec4(0.2+1.5*tempColor.rgb,tempColor.r/2.0 +0.5);

}    


