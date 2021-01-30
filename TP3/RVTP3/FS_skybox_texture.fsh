varying highp vec4 outColor;
varying highp vec3 outTexCoord;
uniform samplerCube texture0;

void main(void)
{
    //vec3 color = textureCube(texture0, outTexCoord);
    //gl_FragColor = vec4(color, outColor.a);
    gl_FragColor = textureCube(texture0, outTexCoord);
}
