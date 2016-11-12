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
				'curve-style': 'bezier'
			})
		.selector('#13')
			.css({
				'background-image': 'Cytospace/images/spu/Processing.jpg'
				})
		.selector('#14')
			.css({
				'background-image': 'Cytospace/images/spu/Branch_begin.jpg'
				})
		.selector('#15')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_end.jpg'
				})
		.selector('#16')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#17')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#18')
			.css({
				'background-image': 'Cytospace/images/spu/Receive.jpg'
				})
		.selector('#20')
			.css({
				'background-image': 'Cytospace/images/cpu/Receive.jpg'
				})
		.selector('#1')
			.css({
				'background-image': 'Cytospace/images/spu/Data_structure.jpg'
				})
		.selector('#2')
			.css({
				'background-image': 'Cytospace/images/spu/Data_structure.jpg'
				})
		.selector('#8')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple_tmp.jpg'
				})
		.selector('#19')
			.css({
				'background-image': 'Cytospace/images/spu/Data_tag.jpg'
				})
		.selector('#4')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple.jpg'
				}),
   elements: {
      nodes: [
		{ data: { id: '13' } },
		{ data: { id: '14' } },
		{ data: { id: '15' } },
		{ data: { id: '16' } },
		{ data: { id: '17' } },
		{ data: { id: '18' } },
		{ data: { id: '20' } },
		{ data: { id: '7' } },
		{ data: { id: '1' } },
		{ data: { id: '2' } },
		{ data: { id: '8' } },
		{ data: { id: '19' } },
		{ data: { id: '4' } }
      ],
      edges: [
		{ data: { source: '2', target: '13' } },
		{ data: { source: '8', target: '13' } },
		{ data: { source: '13', target: '1' } },
		{ data: { source: '13', target: '14' } },
		{ data: { source: '14', target: '15' } },
		{ data: { source: '14', target: '20' } },
		{ data: { source: '15', target: '17' } },
		{ data: { source: '16', target: '18' } },
		{ data: { source: '18', target: '19' } },
		{ data: { source: '18', target: '14' } },
		{ data: { source: '19', target: '14' } },
		{ data: { source: '20', target: '8' } },
		{ data: { source: '20', target: '13' } },
		{ data: { source: '13', target: '11' } }
      ]
   },
   layout: {
		name: 'breadthfirst',
		directed: true,
		padding: 10
	}
});
});
