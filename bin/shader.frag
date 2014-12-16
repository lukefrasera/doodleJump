varying vec2 v_UV;
uniform sampler2D gSampler;

void main(){
	gl_FragColor = texture2D(gSampler, vec2(v_UV[0], v_UV[1]));
}
