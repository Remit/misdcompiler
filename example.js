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
		.selector('#11')
			.css({
				'background-image': 'Cytospace/images/cpu/Define.jpg'
				})
		.selector('#12')
			.css({
				'background-image': 'Cytospace/images/spu/Processing.jpg'
				})
		.selector('#13')
			.css({
				'background-image': 'Cytospace/images/spu/Processing.jpg'
				})
		.selector('#14')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_cond_begin.jpg'
				})
		.selector('#15')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_end.jpg'
				})
		.selector('#16')
			.css({
				'background-image': 'Cytospace/images/spu/Processing.jpg'
				})
		.selector('#17')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_cond_begin.jpg'
				})
		.selector('#18')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_end.jpg'
				})
		.selector('#19')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#20')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#1')
			.css({
				'background-image': 'Cytospace/images/spu/Data_structure.jpg',
				'label': 'STRUCT1'
				})
		.selector('#8')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple.jpg',
				'label': 'x'
				})
		.selector('#9')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple.jpg',
				'label': 'y'
				})
		.selector('#10')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple.jpg',
				'label': 'z'
				}),
   elements: {
      nodes: [
		{ data: { id: '11' }, position: { x: 0, y: 150 } },
		{ data: { id: '12' }, position: { x: 0, y: 600 } },
		{ data: { id: '13' }, position: { x: 150, y: 600 } },
		{ data: { id: '14' }, position: { x: 0, y: 450 } },
		{ data: { id: '15' }, position: { x: 0, y: 750 } },
		{ data: { id: '16' }, position: { x: 300, y: 450 } },
		{ data: { id: '17' }, position: { x: 0, y: 300 } },
		{ data: { id: '18' }, position: { x: 0, y: 900 } },
		{ data: { id: '19' }, position: { x: 0, y: 0 } },
		{ data: { id: '20' }, position: { x: 0, y: 1050 } },
		{ data: { id: '1' }, position: { x: 800, y: 0 } },
		{ data: { id: '8' }, position: { x: 800, y: 150 } },
		{ data: { id: '9' }, position: { x: 800, y: 300 } },
		{ data: { id: '10' }, position: { x: 800, y: 450 } }
      ],
      edges: [
		{ data: { source: '8', target: '12' } },
		{ data: { source: '8', target: '13' } },
		{ data: { source: '8', target: '14' } },
		{ data: { source: '8', target: '16' } },
		{ data: { source: '9', target: '13' } },
		{ data: { source: '9', target: '14' } },
		{ data: { source: '9', target: '16' } },
		{ data: { source: '10', target: '12' } },
		{ data: { source: '10', target: '14' } },
		{ data: { source: '11', target: '17' } },
		{ data: { source: '12', target: '1' } },
		{ data: { source: '12', target: '15' } },
		{ data: { source: '13', target: '1' } },
		{ data: { source: '13', target: '15' } },
		{ data: { source: '14', target: '12' } },
		{ data: { source: '14', target: '13' } },
		{ data: { source: '15', target: '18' } },
		{ data: { source: '16', target: '1' } },
		{ data: { source: '16', target: '18' } },
		{ data: { source: '17', target: '14' } },
		{ data: { source: '17', target: '16' } },
		{ data: { source: '18', target: '20' } },
		{ data: { source: '19', target: '11' } },
		{ data: { source: '23', target: '0' } }
      ]
   },
   layout: {
		name: 'preset',
		directed: true,
		padding: 10
	}
});
});
