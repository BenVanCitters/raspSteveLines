precision highp float;

uniform sampler2D tex0;
uniform vec2 texOffset;
uniform vec2 resolution;
uniform float time;

void main(void)
 {
vec2 texCoord = gl_FragCoord.xy / resolution.xy;

    vec4 vertTexCoord = vec4(texCoord.x,texCoord.y,0,0);

    float sTm = time/1.0;
    vec4 snScl =vec4(25.0*cos(sTm/5.0-1.0),
                     11.0*sin(-sTm/9.0+2.2),
                     16.0*cos(-sTm/8.0+4.2),
                     18.0*sin(sTm/7.0+2.1));
    
    float ofsetScale = 0.1*cos(sTm/35.0);
    vec2 snOffs = ofsetScale * vec2(cos(time+vertTexCoord.t*snScl[0]+vertTexCoord.s*snScl[1]),
                                  sin(time/2.0+vertTexCoord.t*snScl[2]+vertTexCoord.s*snScl[3]));
  // http://www.idevgames.com/forums/thread-3467.html
  vec2 tc0 = vertTexCoord.st + vec2(-texOffset.s, -texOffset.t)+snOffs;
  vec2 tc1 = vertTexCoord.st + vec2(         0.0, -texOffset.t)+snOffs;
  vec2 tc2 = vertTexCoord.st + vec2(+texOffset.s, -texOffset.t)+snOffs;
  vec2 tc3 = vertTexCoord.st + vec2(-texOffset.s,          0.0)+snOffs;
  vec2 tc4 = vertTexCoord.st + vec2(         0.0,          0.0)+snOffs;
  vec2 tc5 = vertTexCoord.st + vec2(+texOffset.s,          0.0)+snOffs;
  vec2 tc6 = vertTexCoord.st + vec2(-texOffset.s, +texOffset.t)+snOffs;
  vec2 tc7 = vertTexCoord.st + vec2(         0.0, +texOffset.t)+snOffs;
  vec2 tc8 = vertTexCoord.st + vec2(+texOffset.s, +texOffset.t)+snOffs;

  vec4 col0 = texture2D(tex0, tc0);
  vec4 col1 = texture2D(tex0, tc1);
  vec4 col2 = texture2D(tex0, tc2);
  vec4 col3 = texture2D(tex0, tc3);
  vec4 col4 = texture2D(tex0, tc4);
  vec4 col5 = texture2D(tex0, tc5);
  vec4 col6 = texture2D(tex0, tc6);
  vec4 col7 = texture2D(tex0, tc7);
  vec4 col8 = texture2D(tex0, tc8);

  vec4 sum = (1.0 * col0 + 2.0 * col1 + 1.0 * col2 +  
              2.0 * col3 + 4.0 * col4 + 2.0 * col5 +
              1.0 * col6 + 2.0 * col7 + 1.0 * col8) / 16.0;            
  float darkMult = 0.7 + 0.3*sin(time/13.3);
  gl_FragColor = vec4(darkMult*sum.rgb, 1);
}    


