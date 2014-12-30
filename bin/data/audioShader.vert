attribute vec4 position;

attribute float audioLevel;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
varying float col;

void main()
{
	vec4 pos = projectionMatrix * modelViewMatrix * position;
	pos += vec4(0,audioLevel,0,0);
	col = audioLevel;
	//pos.y = pos.y + 2 * audioLevel;
	gl_Position = pos;
}
