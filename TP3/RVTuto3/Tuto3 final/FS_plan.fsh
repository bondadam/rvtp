varying highp vec4 outColor;

void main(void)
{
    float t = 1.0 - gl_FragCoord.z;
    gl_FragColor.rgb = t*outColor.rgb;
    gl_FragColor.a = outColor.a;
}
