varying highp vec4 outColor;
varying highp vec2 outTexCoord;
uniform sampler2D texture0;

void main(void)
{
    vec3 color = texture2D(texture0, outTexCoord).rgb * outColor.rgb;
    gl_FragColor = vec4(color, outColor.a);
}
