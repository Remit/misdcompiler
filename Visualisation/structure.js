$(function(){
var cy = cytoscape({
   container: document.getElementById('cy'),
   boxSelectionEnabled: false,
   autounselectify: true,

   style: cytoscape.stylesheet()
		.selector('node')
			.css({
				'height': 80,
				'width': 80,
				'background-fit': 'cover',
				'border-color': '#000',
				'border-width': 3,
				'border-opacity': 0.5
			})
		.selector('edge')
			.css({
				'width': 6,
				'target-arrow-shape': 'triangle',
				'line-color': '#ffaaaa',
				'target-arrow-color': '#ffaaaa',
				'curve-style': 'unbundled-bezier',
				'control-point-distance': '20px'
			})
		.selector('#14')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#15')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				}),
   elements: {
      nodes: [
		{ data: { id: '14' }, position: { x: 0, y: 0 } },
		{ data: { id: '15' }, position: { x: 0, y: 150 } }
      ],
      edges: [
		{ data: { source: '14', target: '15' } },
		{ data: { source: '1', target: '0' } }
      ]
   },
   layout: {
		name: 'preset',
		directed: true,
		padding: 10
	}
});
});
