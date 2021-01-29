varying highp vec3 outColor;
uniform highp float u_Opacity;
uniform vec2 u_resolution;

void main(void)
{
    vec3 st = vec3(vec2(gl_FragCoord.xy/u_resolution), 1);
    vec3 new_color = mix(st, outColor, 0.5f);
    gl_FragColor = vec4(new_color, u_Opacity);
}
